#include "CASSIA.h"

//' @export
// [[Rcpp::export]]
Rcpp::List CASSIA_soil(int start_year,
                       int end_year,

                       Rcpp::DataFrame weather,
                       std::vector<double> GPP_ref,

                       std::vector<double> pPREL,
                       Rcpp::DataFrame pCASSIA_parameters,
                       Rcpp::DataFrame pCASSIA_common,
                       Rcpp::DataFrame pCASSIA_ratios,
                       Rcpp::DataFrame pCASSIA_sperling,
                       std::vector<double> parameters_R,

                       double needle_mass_in, // The value of this should be 0 if you want the needle value to be calculated
                       double Throughfall,
                       int trenching_year,

                       Rcpp::List settings) {

  /*
   * Read into structures
   */

  p1 parSite = make_p1(pPREL);
  p2 parGPP = make_p2(pPREL);
  p3 parET = make_p3(pPREL);
  p4 parSnowRain = make_p4(pPREL);
  p5 parWater = make_p5(pPREL);
  p7 parN = make_p7(pPREL);

  CASSIA_common common = make_common(pCASSIA_common);
  CASSIA_parameters parameters = make_CASSIA_parameters(pCASSIA_parameters, pCASSIA_sperling);
  CASSIA_ratios ratios = make_ratios(pCASSIA_ratios);
  parameters_soil parameters_in = parameters_initalise_test(parameters_R);
  // As C_fungal: 50:50 mantle and ERM, Meyer 2010
  // parameters_in.mantle_mass = MYTCOFON_out.C_fungal/2; // Meyer 2010
  // parameters_in.ERM_mass = MYTCOFON_out.C_fungal/2; // Meyer 2010

  phydro_canopy_parameters phydro_parameters; // TODO: make this into the inputs

  Settings boolsettings = parseSettings(settings);

  /*
   * Weather input made into vectors
   */

  std::vector<double> PAR = weather["PAR"];
  std::vector<double> VPD = weather["VPD"];
  std::vector<double> fAPAR = weather["fAPAR"];
  std::vector<double> Nitrogen = weather["Nitrogen"];
  std::vector<double> Photosynthesis_IN = weather["P"];
  std::vector<double> TAir = weather["T"];
  std::vector<double> TSoil_A = weather["TSA"];
  std::vector<double> TSoil_B = weather["TSB"];
  std::vector<double> Soil_Moisture = weather["MB"];
  std::vector<double> Precip  = weather["Rain"];
  std::vector<double> CO2 = weather["CO2"];
  // TODO: make the PA value input or remove it from the code!
  // std::vector<double> PA = weather["PA"];

  /*
   * Structures set up
   */

  // Forward init values (previous day values) as first values of result vectors

  bool tree_alive = true;

  // std::vector<double> SW, Canopywater, SOG, S;

  /*
   * SW.push_back(SWinit);
   Canopywater.push_back(CWinit);
   SOG.push_back(SOGinit);
   S.push_back(Sinit);
   */

  double CH = parameters.density_tree * parameters.carbon_share;
  double M_suc = 12 * common.M_C + 22 * common.M_H + 11 * common.M_O;

  carbo_tracker Ad;
  Ad.needles = parameters.Ad0_needles;
  Ad.phloem = parameters.Ad0_phloem;
  Ad.xylem_sh = parameters.Ad0_xylem_sh;
  Ad.xylem_st = parameters.Ad0_xylem_st;
  Ad.roots = parameters.Ad0_roots;

  repola_out repola_values;
  if (needle_mass_in == 0) { // The value of this should be 0 if you want the needle value to be calculated
    repola_values = repola(parameters); // TODO: fix
  } else {
    repola_values.needle_mass = needle_mass_in;
  }

  /*
   * Vectors between iterations
   */

  growth_values_out growth_values_for_next_iteration;
  carbo_balance sugar_values_for_next_iteration;
  carbo_balance original_parameters;
  MYCOFON_function_out MYCOFON_for_next_iteration;
  SYMPHONY_output soil_values_for_next_iteration;

  /*
   * Vectors for the outputs
   */

  growth_vector potential_growth_output;
  growth_vector actual_growth_output;
  growth_vector culm_growth;
  PlantAssimilationResult phydro_assimilation;
  culm_growth.height.push_back(parameters.h0);
  culm_growth.roots.push_back(0.1); // TODO: what is the initialisation here? Surely there is a value for this!
  culm_growth.needles.push_back(repola_values.needle_mass);
  biomass_vector biomass_output;
  sugar_values_vector sugar_values_output;
  photo_out_vector photosynthesis_output;
  resp_vector respiration_output;
  MYCOFON_vector MYCOFON_output;
  SYMPHONY_vector soil_output;
  needle_cohorts last_cohorts;
  double last_year_HH;
  double last_year_maxN;
  double GPP_mean;
  std::vector<double> GPP_previous_sum;
  SYMPHONY_output soil_reset;
  MYCOFON_function_out MYCOFON_reset;
  GPP_previous_sum.push_back(481.3); // TODO; make this a variable input, rather than this 2015 value
  double respiration_maintanence;
  std::vector<double> potenital_growth_use;

  /*
   * YEAR LOOP
   */
  std::vector<int> years;
  std::vector<int> days;

  std::vector<int> years_for_runs;
  int years_temparary = start_year;
  double end = 2*(end_year - start_year + 1);
  for (int i=1; i <= end; i++) {
    years_for_runs.push_back(years_temparary);
    if (i%2!=0) {
      years_temparary = years_temparary;
    } else {
      years_temparary = years_temparary+1;
    }
  }

  int final_year = 1;
  for (int year : years_for_runs)  {
    bool trenching;
    if (year > trenching_year)  {
      trenching = true;
    } else {
      trenching = false;
    }

    /*
     * Daily output
     */

    carbo_tracker carbo_tracker_vector;
    xylogensis_out xylogensis_vector;
    double fS;

    /*
     * Yearly initialization
     */

    // Temperature equilibrium for the sugar model
    //	# Compute initial Te by the mean temperature for the first week of # October plus 3C (for the exponential nature of the curves)
    double equilibrium_temperature = (TAir[244] + TAir[245] + TAir[246] + TAir[247] + TAir[248] + TAir[249] + TAir[250] + TAir[251]) / 7 + 3;

    // B0, D00 and h00
    double B0 = M_PI/4.0 * pow(parameters.D0, 2.0);
    double D00 = parameters.D0;
    double h00 = parameters.h0;
    if (boolsettings.xylogensis_option) {
      double LH0 = parameters.h_increment / (0.5 * parameters.sHc);
      double LN0 = parameters.n_length / (0.5 * 4.641331 * parameters.sNc); // TODO: this had a typo in it, check the formula
      double LR0 = 2.0 * parameters.m_R_tot / parameters.sRc; // TODO: check if these parameters are updated somewhere
    }

    /*
     * NEEDLE MASS CALCULATION
     *
     * If it is the first year, then there is no needle mass initialized,
     * after this if there is growth in the model the needle mass is calculated based on last year
     * if there is no growth then the needle mass stays at the originally calculated value
     */

    if (boolsettings.needle_mass_grows) {
      repola_values = repola(parameters); // Needle mass is then calculated on the next D0 and h0 values
    } else {
      repola_values.needle_mass = needle_mass_in;
    }

    needle_cohorts needles_cohorts;
    if (year > start_year) {
      // TODO: parameters, although it is okay as this is Hyytiälä, it should be updated when the other model is updated
      needles_cohorts.year_1 = 31.24535 / parameters.n_length * repola_values.needle_mass / 3.0;
      needles_cohorts.year_2 = last_cohorts.year_1;
      needles_cohorts.year_3 = last_cohorts.year_2;
    }
    double HH, GPP_sum_yesterday, GPP_sum;;
    double needles_last;
    if (year == start_year) {
      last_year_HH = 275.4137;
    }

    // TODO: There should also be xylogenesis dependency here!

    /*
     * Days per year
     */

    int days_per_year = leap_year(year);
    if (boolsettings.CASSIA_graphs) {
      days_per_year = 365;
    }
    /*
     * Yearly initial conditions updated
     */

    // Set up the initial conditions
    yearly_in yearly = yearly_initial_conditions(days_per_year); // TODO: growth should be added to this!

    /*
     * DAYS LOOP
     */
    photosynthesis_out photosynthesis_old;
    for (int day = 0; day < days_per_year; day++) {

      /*
       * PHOTOSYNTHESIS
       *
       * There are yearly, but not daily dependencies other than environmental states here!
       */

      // Uses the method from Tian 2021
      // Extinction coefficient 0.52 is from Tian 2021 as well
      // LAI value is fairly constant if we look at Rautiainen 2012, LAI ~ 3
      double LAI = 3; // TODO
      double f_modifer = needles_last/growth_values_for_next_iteration.max_N;
      double LAI_within_year;
      if (day < 182) { // TODO: I decided that the start of July is the end of spring
        LAI_within_year = 2.0/3.0*LAI + f_modifer*1.0/3.0*LAI;
      } else if (day > 244) { // TODO: I decided that the end of august is the start of autumn
        LAI_within_year = 2.0/3.0*LAI + fS*1.0/3.0*LAI;
      } else {
        LAI_within_year = LAI;
      }
      double fAPAR = (1.0 - std::exp(-0.52 * LAI_within_year));  // TODO: Check this is sensible

      photosynthesis_out photosynthesis;
      double photosynthesis_per_stem;
      double theta, theta_snow, theta_canopy, Throughfall, S, PhenoS,
      Snowmelt, intercepted, Drainage, canw, fE, transp, evap, fWE, fW, gpp380;
      if ((day == 1) && (year == start_year)) {
        theta = parWater.SW; // Correct
        theta_canopy = parWater.CW; // Correct
        theta_snow = parWater.SOG; // Correct
        gpp380 = 0.0; // Correct
        S = parWater.S; // Correct
        PhenoS = 0.0; // Correct
        fE = 0.0;
        Throughfall = 0.0;
        Snowmelt = 0.0;
        intercepted = 0.0;
        Drainage = 0.0;
        canw = 0.0;
        transp = 0.0;
        evap = 0.0;
        fWE = 0.0;
        fW = 0.0;
      } else {
        theta = photosynthesis_old.theta;
        theta_canopy = photosynthesis_old.theta_canopy;
        theta_snow = photosynthesis_old.theta_snow;
        gpp380 = photosynthesis_old.gpp380;
        S = photosynthesis_old.S_state;
        PhenoS = photosynthesis_old.PhenoS;
        fE = photosynthesis_old.fE;
        Throughfall = photosynthesis_old.Throughfall;
        Snowmelt = photosynthesis_old.Snowmelt;
        intercepted = photosynthesis_old.intercepted;
        Drainage = photosynthesis_old.Drainage;
        canw = photosynthesis_old.canw;
        transp = photosynthesis_old.transp;
        evap = photosynthesis_old.evap;
        fWE = photosynthesis_old.fWE;
        fW = photosynthesis_old.fW;
      }

      if (boolsettings.photosynthesis_as_input) {
        photosynthesis.GPP = Photosynthesis_IN[day];
        photosynthesis_per_stem = Photosynthesis_IN[day] / 1010 * 10000/1000;
      } else {
        if (boolsettings.phydro) {
          double lai = 1.8; // TODO: add a value here?
          double mass_to_area = 1.8; // TODO: add a value here?
          double crown_area = culm_growth.needles[day-1] * mass_to_area; // TODO: check that the canopy area is the whole area rather than the intercepting area
          double zeta = crown_area / culm_growth.roots[day-1];
          double n_layers = 3; // TODO: does this need to be predetermined in the canopy area / env bits
          // TODO: note that nitrogen is the nitrogen store in the leaf rather than the nitrogen input overall
          double Nitrogen = 1; // Currently no functions for this!

          double PA = 1000;
          double SWP = 0.01;

          double fipar = 0.7; // TODO: real value

          //phydro_assimilation = calc_plant_assimilation_rate(fipar,
          //                                                   PAR[day], TAir[day], VPD[day], Precip[day], CO2[day], Nitrogen, PA, SWP,
          //                                                   phydro_parameters, lai, n_layers, crown_area, culm_growth.height[day-1], zeta);

          // TODO: need to check the exact unit of GPP going into the model
          //photosynthesis.GPP = phydro_assimilation.gpp;


        } else {
          double fAPAR = 0.7; // TODO: just for the first checks
          photosynthesis = preles(day, PAR[day], TAir[day], VPD[day], Precip[day],
                                  CO2[day], fAPAR, Nitrogen[day],
                                  parSite, parGPP, parET, parSnowRain, parWater, parN,
                                  boolsettings.etmodel, theta, theta_snow, theta_canopy, Throughfall,
                                  S, PhenoS, Snowmelt, intercepted, Drainage, canw,
                                  fE, transp, evap, fWE, fW, gpp380);

          photosynthesis_per_stem = photosynthesis.GPP / 1010 * 10000/1000;
          fS = photosynthesis.fS;

          photosynthesis_old = photosynthesis;
        }
      }

      if (day == 0) {
        GPP_sum = 0.0;
      } else if (day <= 182) {
        GPP_sum = GPP_sum_yesterday;
      } else if (day > 182 && day <= 244) {
        GPP_sum = GPP_sum_yesterday + photosynthesis.GPP;
      } else if (day > 245) {
        GPP_sum = GPP_sum_yesterday;
      }

      /*
       * Potential Growth
       *
       * In terms of the adaptation from the R code, the potential values are not altered by daily processes so still calculate them for a year
       */

      double en_pot_growth_old;
      if (day < 11) {
        en_pot_growth_old = 0.0;
      } else {
        en_pot_growth_old = potenital_growth_use[day-11];
      }

      GPP_mean = 463.8833; // TODO: move when I understand GPP_sum
      growth_out potential_growth = growth(day, year, TAir[day], TSoil_A[day], TSoil_B[day], Soil_Moisture[day], photosynthesis.GPP, GPP_ref[day],
                                           boolsettings.root_as_Ding, boolsettings.xylogensis_option, boolsettings.environmental_effect_xylogenesis, boolsettings.sD_estim_T_count,
                                           common, parameters, ratios,
                                           CH, B0, GPP_mean, GPP_previous_sum[year-start_year],
                                           boolsettings.LH_estim, boolsettings.LN_estim, boolsettings.LD_estim,
                                           // Last iteration value
                                           boolsettings.tests, growth_values_for_next_iteration, last_year_HH,
                                           days_per_year);
      // Saved for the next iteration
      growth_values_for_next_iteration = potential_growth.previous_values;

      /*
       * Respiration
       *
       * There are yearly, but not daily dependencies other than weather conditions here!
       */

      respiration_out resp = respiration(day, parameters, ratios, repola_values,
                                         TAir[day], TSoil_A[day],
                                         boolsettings.temp_rise, boolsettings.Rm_acclimation, boolsettings.mN_varies,
                                         // parameters that I am not sure about
                                         B0); // TODO: respiration for the fungi and microbes

      /*
       * Sugar
       */

      // TODO; need to check the indexes!
      if (day == 0 && year == start_year) {
        sugar_values_for_next_iteration.sugar.needles = parameters.sugar_needles0;
        sugar_values_for_next_iteration.sugar.phloem = parameters.sugar_phloem0;
        sugar_values_for_next_iteration.sugar.roots = parameters.sugar_roots0;
        sugar_values_for_next_iteration.sugar.xylem_sh = parameters.sugar_xylem_sh0;
        sugar_values_for_next_iteration.sugar.xylem_st = parameters.sugar_xylem_st0;
        sugar_values_for_next_iteration.sugar.mycorrhiza = 0.0; // TODO: think about this

        sugar_values_for_next_iteration.starch.needles = parameters.starch_needles0;
        sugar_values_for_next_iteration.starch.phloem = parameters.starch_phloem0;
        sugar_values_for_next_iteration.starch.roots = parameters.starch_roots0;
        sugar_values_for_next_iteration.starch.xylem_sh = parameters.starch_xylem_sh0;
        sugar_values_for_next_iteration.starch.xylem_st = parameters.starch_xylem_st0;
        sugar_values_for_next_iteration.starch.mycorrhiza = 0.0;
      } else if (day == 0 && year != start_year) {
        sugar_values_for_next_iteration.sugar.needles = parameters.sugar_needles0;
        sugar_values_for_next_iteration.sugar.phloem = parameters.sugar_phloem0;
        sugar_values_for_next_iteration.sugar.roots = parameters.sugar_roots0;
        sugar_values_for_next_iteration.sugar.xylem_sh = parameters.sugar_xylem_sh0;
        sugar_values_for_next_iteration.sugar.xylem_st = parameters.sugar_xylem_st0;
        sugar_values_for_next_iteration.sugar.mycorrhiza = 0.0;

        sugar_values_for_next_iteration.starch.needles = parameters.starch_needles0;
        sugar_values_for_next_iteration.starch.phloem = parameters.starch_phloem0;
        sugar_values_for_next_iteration.starch.roots = parameters.starch_roots0;
        sugar_values_for_next_iteration.starch.xylem_sh = parameters.starch_xylem_sh0;
        sugar_values_for_next_iteration.starch.xylem_st = parameters.starch_xylem_st0;
        sugar_values_for_next_iteration.starch.mycorrhiza = 0.0;
      } else {
        carbo_balance sugar_model_out = sugar_model(year, day, TAir[day], photosynthesis_per_stem,
                                                    common, parameters,
                                                    D00,
                                                    potential_growth.previous_values.sH,
                                                    resp,
                                                    boolsettings.sperling_model,
                                                    tree_alive,
                                                    boolsettings.storage_grows,
                                                    repola_values.needle_mass,
                                                    equilibrium_temperature,
                                                    potential_growth,
                                                    sugar_values_for_next_iteration.sugar,
                                                    sugar_values_for_next_iteration.starch,
                                                    sugar_values_for_next_iteration.previous_values);
        // Saved for the next iteration
        sugar_values_for_next_iteration.previous_values = sugar_model_out.previous_values;
        sugar_values_for_next_iteration.sugar = sugar_model_out.sugar;
        sugar_values_for_next_iteration.starch = sugar_model_out.starch;
        sugar_values_for_next_iteration.storage = sugar_model_out.storage;
        parameters.sB0 = sugar_values_for_next_iteration.previous_values.sB0;
        tree_alive = sugar_model_out.previous_values.tree_alive;
      }

      /*
       * Actual growth
       */

      double n_rows = ratios.form_factor * parameters.h0 / parameters.cell_l_ew * M_PI * parameters.D0 / parameters.cell_d_ew;
      // double GD = // g_sD_T *fD * LD; TODO: where do the parameters come from?
      double ew_cells_vector; // TODO: where does this come from?
      double lw_cells_vector;
      double max_ew_cells = std::max(ew_cells_vector, 0.0); // TODO: make this come from the last iteration?
      double max_lw_cells = std::max(lw_cells_vector, 0.0); // TODO: make this come from the last iteration?

      // TODO: storage
      growth_out actual_growth_out = actual_growth(parameters, common,
                                                   sugar_values_for_next_iteration.storage, potential_growth,
                                                   resp,
                                                   boolsettings.sperling_model);

      // Cumulative values
      culm_growth.height.push_back(culm_growth.height[day-1] + actual_growth_out.height);
      culm_growth.roots.push_back(culm_growth.roots[day-1] + actual_growth_out.roots);
      culm_growth.needles.push_back(culm_growth.needles[day-1] + actual_growth_out.needles);

      /*
       * MYCOFON
       */

      // TODO: work out which parameters are available here
      // TODO: 0.5 is a filler for the C:N ratio of roots, should this be a ratio of the nitrogen stored in the tree?
      if (year == start_year && day == 0) {
        // TODO: NC ratio
        MYCOFON_for_next_iteration.C_biomass = 0.5;
        MYCOFON_for_next_iteration.C_fungal = 0.5; // TODO: replace, just for coding sake
        MYCOFON_for_next_iteration.C_roots_NonStruct = parameters.sugar_roots0;
        MYCOFON_for_next_iteration.C_fungal_NonStruct = parameters.sugar_roots0;
        MYCOFON_for_next_iteration.N_roots_NonStruct = parameters.sugar_roots0 * parameters_in.NC_in_root_opt; // TODO: replace, just for coding sake
        MYCOFON_for_next_iteration.N_fungal_NonStruct = parameters.sugar_roots0 * parameters_in.NC_fungal_opt; // TODO: replace, just for coding sake

        soil_values_for_next_iteration.NH4 = 31.0; // 0.31; // NH40 (Korhonen, 2013)
        soil_values_for_next_iteration.NO3 = 20.0; // 0.002; // NO30 (Korhonen, 2013)
        soil_values_for_next_iteration.N_FOM = 26.0; // Norg0 (Korhonen, 2013)
        soil_values_for_next_iteration.NC_mantle = 0.4; // TODO: input and replace somehow
        soil_values_for_next_iteration.NC_ERM = 0.4; // TODO: input and replace somehow
        soil_values_for_next_iteration.NC_needles = 0.5; // TODO: input and replace somehow
        soil_values_for_next_iteration.NC_woody = 0.5; // TODO: input and replace somehow
        soil_values_for_next_iteration.NC_roots = 0.5; // TODO: input and replace somehow

        // TODO: this should obviously not all be 10 or 0...
        soil_values_for_next_iteration.C_FOM_needles = 20.0;
        soil_values_for_next_iteration.C_FOM_woody = 15.0;
        soil_values_for_next_iteration.C_FOM_roots = 30.0;
        soil_values_for_next_iteration.C_FOM_mantle = 9.0;
        soil_values_for_next_iteration.C_FOM_ERM = 10.0;
        soil_values_for_next_iteration.C_exudes = 0.0;
        soil_values_for_next_iteration.C_SOM = 56.0;
        soil_values_for_next_iteration.N_SOM = 10.0;
        soil_values_for_next_iteration.C_decompose_FOM = 0.2;
        soil_values_for_next_iteration.C_decompose_SOM = 0.2;
        soil_values_for_next_iteration.N_decompose_FOM = 0.2 * parameters_in.NC_microbe_opt;
        soil_values_for_next_iteration.N_decompose_SOM = 0.2 * parameters_in.NC_microbe_opt;
      } else if (year != start_year && day == 0) {
        MYCOFON_for_next_iteration.C_biomass = MYCOFON_reset.C_biomass;
        MYCOFON_for_next_iteration.C_fungal = MYCOFON_reset.C_fungal;
        MYCOFON_for_next_iteration.C_roots_NonStruct = MYCOFON_reset.C_roots_NonStruct;
        MYCOFON_for_next_iteration.C_fungal_NonStruct = MYCOFON_reset.C_fungal_NonStruct;
        MYCOFON_for_next_iteration.N_roots_NonStruct = MYCOFON_reset.N_roots_NonStruct;
        MYCOFON_for_next_iteration.N_fungal_NonStruct = MYCOFON_reset.N_fungal_NonStruct;

        soil_values_for_next_iteration.NH4 = soil_reset.NH4;
        soil_values_for_next_iteration.NO3 = soil_reset.NO3;
        soil_values_for_next_iteration.N_FOM = soil_reset.N_FOM;
        soil_values_for_next_iteration.NC_mantle = soil_reset.NC_mantle;
        soil_values_for_next_iteration.NC_ERM = soil_reset.NC_ERM;
        soil_values_for_next_iteration.NC_needles = soil_reset.NC_needles;
        soil_values_for_next_iteration.NC_woody = soil_reset.NC_woody;
        soil_values_for_next_iteration.NC_roots = soil_reset.NC_roots;

        soil_values_for_next_iteration.C_FOM_needles = soil_reset.C_FOM_needles;
        soil_values_for_next_iteration.C_FOM_woody = soil_reset.C_FOM_woody;
        soil_values_for_next_iteration.C_FOM_roots = soil_reset.C_FOM_roots;
        soil_values_for_next_iteration.C_FOM_mantle = soil_reset.C_FOM_mantle;
        soil_values_for_next_iteration.C_FOM_ERM = soil_reset.C_FOM_ERM;
        soil_values_for_next_iteration.C_exudes = soil_reset.C_exudes;
        soil_values_for_next_iteration.C_SOM = soil_reset.C_SOM;
        soil_values_for_next_iteration.N_SOM = soil_reset.N_SOM;
        soil_values_for_next_iteration.C_decompose_FOM = soil_reset.C_decompose_FOM;
        soil_values_for_next_iteration.C_decompose_SOM = soil_reset.C_decompose_SOM;
        soil_values_for_next_iteration.N_decompose_FOM = soil_reset.N_decompose_FOM;
        soil_values_for_next_iteration.N_decompose_SOM = soil_reset.N_decompose_SOM;
      }

      MYCOFON_for_next_iteration.C_roots_NonStruct = sugar_values_for_next_iteration.sugar.roots;
      if (trenching) {
        MYCOFON_for_next_iteration.C_biomass = 0.0;
        MYCOFON_for_next_iteration.C_roots_NonStruct = 0.0;
        MYCOFON_for_next_iteration.N_roots_NonStruct = 0.0;
      }

      MYCOFON_function_out MYCOFON_out = mycofon_balence(MYCOFON_for_next_iteration.C_biomass,
                                                         actual_growth_out.roots,
                                                         MYCOFON_for_next_iteration.C_fungal,
                                                         potential_growth.ecto,
                                                         MYCOFON_for_next_iteration.C_roots_NonStruct,
                                                         MYCOFON_for_next_iteration.N_roots_NonStruct,
                                                         MYCOFON_for_next_iteration.C_fungal_NonStruct,
                                                         MYCOFON_for_next_iteration.N_fungal_NonStruct,
                                                         sugar_values_for_next_iteration.sugar.mycorrhiza,
                                                         parameters_in,
                                                         soil_values_for_next_iteration.NH4,
                                                         soil_values_for_next_iteration.NO3,
                                                         soil_values_for_next_iteration.N_FOM,
                                                         TAir[day],
                                                         TSoil_B[day],
                                                         Soil_Moisture[day],
                                                         false,
                                                         trenching);
        // TODO: does the sugar balance for this need to be added to the CASSIA model?
      MYCOFON_for_next_iteration = MYCOFON_out;

      /*
       *  Litter
       */

      // Currently a time series - should add litter in the model more explicitly
      // There is a trenched version for Jussi's data

      double Litter_needles, Litter_woody, Litter_roots, Litter_ERM, Little_mantle;
      Litter_needles = 0.1 * (needle_mass_in / 3) / 365;
      Litter_woody = actual_growth_out.wall / (365*3);
      Litter_roots = actual_growth_out.roots / 365;
      Litter_ERM = actual_growth_out.roots / 365;
      Little_mantle = actual_growth_out.roots / 365;

      if (trenching) {
        Litter_needles = 0.0;
        Litter_woody = 0.0;
        Litter_roots = 0.0;

        MYCOFON_for_next_iteration.exudes_plant = 0.0;
      }

      /*
       * SOIL
       */

      // TODO: if there are no roots then there can't be transfers sort this!

      SYMPHONY_output Soil_All = symphony_multiple_FOM_daily(TSoil_B[day], Soil_Moisture[day],
                                                            soil_values_for_next_iteration.C_FOM_needles,
                                                            soil_values_for_next_iteration.C_FOM_woody,
                                                            soil_values_for_next_iteration.C_FOM_roots,
                                                            soil_values_for_next_iteration.C_FOM_mantle,
                                                            soil_values_for_next_iteration.C_FOM_ERM,
                                                            soil_values_for_next_iteration.C_exudes,
                                                            soil_values_for_next_iteration.C_SOM, soil_values_for_next_iteration.N_SOM,
                                                            soil_values_for_next_iteration.C_decompose_FOM, soil_values_for_next_iteration.C_decompose_SOM,
                                                            soil_values_for_next_iteration.N_decompose_FOM, soil_values_for_next_iteration.N_decompose_SOM,
                                                            Litter_needles, Litter_woody, Litter_roots, Little_mantle, Litter_ERM,
                                                            MYCOFON_for_next_iteration.exudes_fungal,
                                                            MYCOFON_for_next_iteration.exudes_plant,
                                                            0.5, 0.5, // TODO: this!
                                                            soil_values_for_next_iteration.NH4, soil_values_for_next_iteration.NO3,
                                                            soil_values_for_next_iteration.NC_needles, soil_values_for_next_iteration.NC_woody,
                                                            soil_values_for_next_iteration.NC_roots, soil_values_for_next_iteration.NC_mantle, soil_values_for_next_iteration.NC_ERM,
                                                            MYCOFON_for_next_iteration.uptake_NH4_plant, MYCOFON_for_next_iteration.uptake_NH4_fungal,
                                                            MYCOFON_for_next_iteration.uptake_NO3_plant, MYCOFON_for_next_iteration.uptake_NO3_fungal,
                                                            MYCOFON_for_next_iteration.uptake_Norg_plant, MYCOFON_for_next_iteration.uptake_Norg_fungal,
                                                            soil_values_for_next_iteration.SOM_Norg_used,
                                                            parameters_in.N_limits_microbes, parameters_in.N_k_microbes, parameters_in.SWC_limits_microbes,
                                                            parameters_in.NC_microbe_opt, parameters_in.microbe_turnover, true);

      /*
       * Output
       */
      HH = potential_growth.previous_values.HH;
      needles_last = potential_growth.needles;
      potenital_growth_use.push_back(potential_growth.use);
      if (!tree_alive) {
        std::cout << "The tree is dead due to sugar storage";
      }

      GPP_sum_yesterday = GPP_sum;

      if (final_year%2==0) {

        // To vectors

        years.push_back(year);
        days.push_back(day);

        respiration_output.maintenance.push_back(actual_growth_out.respiration_maintenance);
        respiration_output.growth.push_back(actual_growth_out.respiration_growth);
        respiration_output.microbes_FOM.push_back(Soil_All.Microbe_respiration_per_mass * Soil_All.C_decompose_FOM);
        respiration_output.microbes_SOM.push_back(Soil_All.Microbe_respiration_per_mass * Soil_All.C_decompose_SOM);
        respiration_output.mycorrhiza.push_back(MYCOFON_for_next_iteration.respiration * MYCOFON_for_next_iteration.C_fungal);

        potential_growth_output.height.push_back(potential_growth.height);
        potential_growth_output.needles.push_back(potential_growth.needles);
        potential_growth_output.roots.push_back(potential_growth.roots);
        potential_growth_output.diameter.push_back(potential_growth.diameter);
        potential_growth_output.bud.push_back(potential_growth.bud);
        potential_growth_output.g.push_back(potential_growth.g);
        potential_growth_output.en_pot_growth.push_back(potential_growth.use);

        actual_growth_output.height.push_back(actual_growth_out.height);
        actual_growth_output.needles.push_back(actual_growth_out.needles);
        actual_growth_output.roots.push_back(actual_growth_out.roots);
        actual_growth_output.diameter.push_back(actual_growth_out.wall);
        actual_growth_output.bud.push_back(actual_growth_out.bud);

        sugar_values_output.sugar.push_back(sugar_values_for_next_iteration.sugar.needles +
          sugar_values_for_next_iteration.sugar.phloem +
          sugar_values_for_next_iteration.sugar.xylem_sh +
          sugar_values_for_next_iteration.sugar.xylem_st +
          sugar_values_for_next_iteration.sugar.roots);
        sugar_values_output.starch.push_back(sugar_values_for_next_iteration.starch.needles +
          sugar_values_for_next_iteration.starch.phloem +
          sugar_values_for_next_iteration.starch.xylem_sh +
          sugar_values_for_next_iteration.starch.xylem_st +
          sugar_values_for_next_iteration.starch.roots);
        sugar_values_output.starch_needles.push_back(sugar_values_for_next_iteration.starch.needles);
        sugar_values_output.starch_phloem.push_back(sugar_values_for_next_iteration.starch.phloem);
        sugar_values_output.starch_xylem_sh.push_back(sugar_values_for_next_iteration.starch.xylem_sh);
        sugar_values_output.starch_xylem_st.push_back(sugar_values_for_next_iteration.starch.xylem_st);
        sugar_values_output.starch_roots.push_back(sugar_values_for_next_iteration.starch.roots);
        sugar_values_output.starch_mycorrhiza.push_back(sugar_values_for_next_iteration.starch.mycorrhiza);
        sugar_values_output.sugar_needles.push_back(sugar_values_for_next_iteration.sugar.needles);
        sugar_values_output.sugar_phloem.push_back(sugar_values_for_next_iteration.sugar.phloem);
        sugar_values_output.sugar_xylem_sh.push_back(sugar_values_for_next_iteration.sugar.xylem_sh);
        sugar_values_output.sugar_xylem_st.push_back(sugar_values_for_next_iteration.sugar.xylem_st);
        sugar_values_output.sugar_roots.push_back(sugar_values_for_next_iteration.sugar.roots);
        sugar_values_output.sugar_mycorrhiza.push_back(sugar_values_for_next_iteration.sugar.mycorrhiza);

        photosynthesis_output.GPP.push_back(photosynthesis.GPP);
        photosynthesis_output.ET.push_back(photosynthesis.ET);
        photosynthesis_output.SoilWater.push_back(photosynthesis.SoilWater);
        photosynthesis_output.fS.push_back(photosynthesis.fS);

        soil_output.C_decompose_FOM.push_back(Soil_All.C_decompose_FOM);
        soil_output.C_decompose_SOM.push_back(Soil_All.C_decompose_SOM);
        soil_output.C_FOM_ERM.push_back(Soil_All.C_FOM_ERM);
        soil_output.C_FOM_mantle.push_back(Soil_All.C_FOM_mantle);
        soil_output.C_FOM_needles.push_back(Soil_All.C_FOM_needles);
        soil_output.C_FOM_roots.push_back(Soil_All.C_FOM_roots);
        soil_output.C_FOM_woody.push_back(Soil_All.C_FOM_woody);
        soil_output.C_exudes.push_back(Soil_All.C_exudes);
        soil_output.C_SOM.push_back(Soil_All.C_SOM);
        soil_output.N_decompose_FOM.push_back(Soil_All.N_decompose_FOM);
        soil_output.N_decompose_SOM.push_back(Soil_All.N_decompose_SOM);
        soil_output.N_FOM.push_back(Soil_All.N_FOM);
        soil_output.N_SOM.push_back(Soil_All.N_SOM);
        soil_output.NC_ERM.push_back(Soil_All.NC_ERM);
        soil_output.NC_mantle.push_back(Soil_All.NC_mantle);
        soil_output.NC_needles.push_back(Soil_All.NC_needles);
        soil_output.NC_roots.push_back(Soil_All.NC_roots);
        soil_output.NC_woody.push_back(Soil_All.NC_roots);
        soil_output.NH4.push_back(Soil_All.NH4);
        soil_output.NO3.push_back(Soil_All.NO3);
        soil_output.SOM_Norg_used.push_back(Soil_All.SOM_Norg_used);
        soil_output.Microbe_respiration.push_back(Soil_All.Microbe_respiration_per_mass);
        soil_output.NH4_Uptake_Microbe_FOM.push_back(Soil_All.NH4_Uptake_Microbe_FOM);
        soil_output.NO3_Uptake_Microbe_FOM.push_back(Soil_All.NO3_Uptake_Microbe_FOM);
        soil_output.Norg_Uptake_Microbe_FOM.push_back(Soil_All.Norg_Uptake_Microbe_FOM);
        soil_output.C_Uptake_Microbe_FOM.push_back(Soil_All.C_Uptake_Microbe_FOM);
        soil_output.NH4_Uptake_Microbe_SOM.push_back(Soil_All.NH4_Uptake_Microbe_SOM);
        soil_output.NO3_Uptake_Microbe_SOM.push_back(Soil_All.NO3_Uptake_Microbe_SOM);
        soil_output.Norg_Uptake_Microbe_SOM.push_back(Soil_All.Norg_Uptake_Microbe_SOM);
        soil_output.C_Uptake_Microbe_SOM.push_back(Soil_All.C_Uptake_Microbe_SOM);

        if (day == 364) {
          soil_reset.C_FOM_needles = Soil_All.C_FOM_needles;
          soil_reset.C_FOM_woody = Soil_All.C_FOM_woody;
          soil_reset.C_FOM_roots = Soil_All.C_FOM_roots;
          soil_reset.C_FOM_mantle = Soil_All.C_FOM_mantle;
          soil_reset.C_FOM_ERM = Soil_All.C_FOM_ERM;
          soil_reset.C_exudes = Soil_All.C_exudes;
          soil_reset.C_SOM = Soil_All.C_SOM;
          soil_reset.N_SOM = Soil_All.N_SOM;
          soil_reset.N_FOM = Soil_All.N_FOM;
          soil_reset.C_decompose_FOM = Soil_All.C_decompose_FOM;
          soil_reset.C_decompose_SOM = Soil_All.C_decompose_SOM;
          soil_reset.N_decompose_FOM = Soil_All.N_decompose_FOM;
          soil_reset.N_decompose_SOM = Soil_All.N_decompose_SOM;
          soil_reset.NC_ERM = Soil_All.NC_ERM;
          soil_reset.NC_mantle = Soil_All.NC_mantle;
          soil_reset.NC_needles = Soil_All.NC_needles;
          soil_reset.NC_roots = Soil_All.NC_roots;
          soil_reset.NC_woody = Soil_All.NC_roots;
          soil_reset.NH4 = Soil_All.NH4;
          soil_reset.NO3 = Soil_All.NO3;
          soil_reset.SOM_Norg_used = Soil_All.SOM_Norg_used;
        }

        MYCOFON_output.C_biomass.push_back(MYCOFON_for_next_iteration.C_biomass);
        MYCOFON_output.C_roots.push_back(MYCOFON_for_next_iteration.C_roots);
        MYCOFON_output.C_fungal.push_back(MYCOFON_for_next_iteration.C_fungal);
        MYCOFON_output.C_roots_NonStruct.push_back(MYCOFON_for_next_iteration.C_roots_NonStruct);
        MYCOFON_output.C_fungal_NonStruct.push_back(MYCOFON_for_next_iteration.C_fungal_NonStruct);
        MYCOFON_output.N_roots_NonStruct.push_back(MYCOFON_for_next_iteration.N_roots_NonStruct);
        MYCOFON_output.N_fungal_NonStruct.push_back(MYCOFON_for_next_iteration.N_fungal_NonStruct);
        MYCOFON_output.uptake_plant.push_back(MYCOFON_for_next_iteration.uptake_plant);
        MYCOFON_output.uptake_fungal.push_back(MYCOFON_for_next_iteration.uptake_fungal);
        MYCOFON_output.uptake_NH4_plant.push_back(MYCOFON_for_next_iteration.uptake_NH4_plant);
        MYCOFON_output.uptake_NH4_fungal.push_back(MYCOFON_for_next_iteration.uptake_NH4_fungal);
        MYCOFON_output.uptake_NO3_plant.push_back(MYCOFON_for_next_iteration.uptake_NO3_plant);
        MYCOFON_output.uptake_NO3_fungal.push_back(MYCOFON_for_next_iteration.uptake_NO3_fungal);
        MYCOFON_output.uptake_Norg_plant.push_back(MYCOFON_for_next_iteration.uptake_Norg_plant);
        MYCOFON_output.uptake_Norg_fungal.push_back(MYCOFON_for_next_iteration.uptake_Norg_fungal);
        MYCOFON_output.from_CASSIA.push_back(MYCOFON_for_next_iteration.from_CASSIA);
        MYCOFON_output.to_CASSIA.push_back(MYCOFON_for_next_iteration.to_CASSIA);
        MYCOFON_output.exudes_fungal.push_back(MYCOFON_for_next_iteration.exudes_fungal);
        MYCOFON_output.exudes_plant.push_back(MYCOFON_for_next_iteration.exudes_plant);
        MYCOFON_output.Plant_demand.push_back(MYCOFON_for_next_iteration.Plant_demand);
        MYCOFON_output.Fungal_demand.push_back(MYCOFON_for_next_iteration.Fungal_demand);
        MYCOFON_output.Plant_given.push_back(MYCOFON_for_next_iteration.Plant_given);
        MYCOFON_output.Fungal_given.push_back(MYCOFON_for_next_iteration.Fungal_given);

        if (day == 364) {
          MYCOFON_reset.C_biomass = MYCOFON_for_next_iteration.C_biomass;
          MYCOFON_reset.C_fungal = MYCOFON_for_next_iteration.C_fungal;
          MYCOFON_reset.C_roots_NonStruct = MYCOFON_for_next_iteration.C_roots_NonStruct;
          MYCOFON_reset.C_fungal_NonStruct = MYCOFON_for_next_iteration.C_fungal_NonStruct;
          MYCOFON_reset.N_roots_NonStruct = MYCOFON_for_next_iteration.N_roots_NonStruct;
          MYCOFON_reset.N_fungal_NonStruct = MYCOFON_for_next_iteration.N_fungal_NonStruct;
        }
      }
    }

    last_year_HH = HH;

    if (final_year%2==0) {
      GPP_mean = 463.8833; // TODO: should change this!
      GPP_previous_sum.push_back(GPP_sum);

      last_cohorts.year_1 = needles_cohorts.year_1; // TODO: currently the growth doesn't really have an effect on this - should it?
      last_cohorts.year_2 = needles_cohorts.year_2;
      last_cohorts.year_3 = needles_cohorts.year_3;

      parameters.sugar_needles0 = sugar_values_for_next_iteration.sugar.needles;
      parameters.sugar_phloem0 = sugar_values_for_next_iteration.sugar.phloem;
      parameters.sugar_roots0 = sugar_values_for_next_iteration.sugar.roots;
      parameters.sugar_xylem_sh0 = sugar_values_for_next_iteration.sugar.xylem_sh;
      parameters.sugar_xylem_st0 = sugar_values_for_next_iteration.sugar.xylem_st;

      parameters.starch_needles0 = sugar_values_for_next_iteration.starch.needles;
      parameters.starch_phloem0 = sugar_values_for_next_iteration.starch.phloem;
      parameters.starch_roots0 = sugar_values_for_next_iteration.starch.roots;
      parameters.starch_xylem_sh0 = sugar_values_for_next_iteration.starch.xylem_sh;
      parameters.starch_xylem_st0 = sugar_values_for_next_iteration.starch.xylem_st;
    }

    // TODO: need to add the growth of things here!
    final_year = final_year + 1;

    if (year == final_year + 1) {
      parameters.sugar_needles0 = original_parameters.sugar.needles;
      parameters.sugar_phloem0 = original_parameters.sugar.phloem;
      parameters.sugar_roots0 = original_parameters.sugar.roots;
      parameters.sugar_xylem_sh0 = original_parameters.sugar.xylem_sh;
      parameters.sugar_xylem_st0 = original_parameters.sugar.xylem_st;

      parameters.starch_needles0 = original_parameters.starch.needles;
      parameters.starch_phloem0 = original_parameters.starch.phloem;
      parameters.starch_roots0 = original_parameters.starch.roots;
      parameters.starch_xylem_sh0 = original_parameters.starch.xylem_sh;
      parameters.starch_xylem_st0 = original_parameters.starch.xylem_st;
    }
  }

  ///////////////////////
  // Output
  ///////////////////////

  // Dataframes

  Rcpp::DataFrame df = Rcpp::DataFrame::create(Rcpp::_["year"] = years,
                                               Rcpp::_["day"] = days,
                                               Rcpp::_["g"] = potential_growth_output.g,
                                               Rcpp::_["bud_growth_potential"] = potential_growth_output.bud,
                                               Rcpp::_["wall_growth_potential"] = potential_growth_output.diameter,
                                               Rcpp::_["needle_growth_potential"] = potential_growth_output.needles,
                                               Rcpp::_["roots_growth_potential"] = potential_growth_output.roots,
                                               Rcpp::_["height_growth_potential"] = potential_growth_output.height,
                                               Rcpp::_["bud_growth"] = actual_growth_output.bud,
                                               Rcpp::_["diameter_growth"] = actual_growth_output.diameter,
                                               Rcpp::_["needle_growth"] = actual_growth_output.needles,
                                               Rcpp::_["root_growth"] = actual_growth_output.roots,
                                               Rcpp::_["height_growth"] = actual_growth_output.height,
                                               Rcpp::_["respiration_growth"] = respiration_output.growth,
                                               Rcpp::_["respiration_maintenance"] = respiration_output.maintenance,
                                               Rcpp::_["Microbe_respiration"] = soil_output.Microbe_respiration,
                                               Rcpp::_["ring_width"] = 0.0); // TODO: where is the ring width?
  Rcpp::DataFrame df2 = Rcpp::DataFrame::create(Rcpp::_["sugar"] = sugar_values_output.sugar,
                                                Rcpp::_["starch"] = sugar_values_output.starch,
                                                Rcpp::_["starch_needles"] = sugar_values_output.starch_needles,
                                                Rcpp::_["starch_phloem"] = sugar_values_output.starch_phloem,
                                                Rcpp::_["starch_xylem_sh"] = sugar_values_output.starch_xylem_sh,
                                                Rcpp::_["starch_xylem_st"] = sugar_values_output.starch_xylem_st,
                                                Rcpp::_["starch_roots"] = sugar_values_output.starch_roots,
                                                Rcpp::_["starch_mycorrhiza"] = sugar_values_output.starch_mycorrhiza,
                                                Rcpp::_["sugar_needles"] = sugar_values_output.sugar_needles,
                                                Rcpp::_["sugar_phloem"] = sugar_values_output.sugar_phloem,
                                                Rcpp::_["sugar_xylem_sh"] = sugar_values_output.sugar_xylem_sh,
                                                Rcpp::_["sugar_xylem_st"] = sugar_values_output.sugar_xylem_st,
                                                Rcpp::_["sugar_roots"] = sugar_values_output.sugar_roots,
                                                Rcpp::_["sugar_mycorrhiza"] = sugar_values_output.sugar_mycorrhiza,
                                                Rcpp::_["n_E_pot"] = growth_values_for_next_iteration.n_E_pot,
                                                Rcpp::_["n_W_pot"] = growth_values_for_next_iteration.n_W_pot,
                                                Rcpp::_["n_M_pot"] = growth_values_for_next_iteration.n_M_pot);
  Rcpp::DataFrame df3 = Rcpp::DataFrame::create(Rcpp::_["C_decompose_FOM"] = soil_output.C_decompose_FOM,
                                                Rcpp::_["C_decompose_SOM"] = soil_output.C_decompose_SOM,
                                                Rcpp::_["C_FOM_ERM"] = soil_output.C_FOM_ERM,
                                                Rcpp::_["C_FOM_mantle"] = soil_output.C_FOM_mantle,
                                                Rcpp::_["C_FOM_needles"] = soil_output.C_FOM_needles,
                                                Rcpp::_["C_FOM_roots"] = soil_output.C_FOM_roots,
                                                Rcpp::_["C_FOM_woody"] = soil_output.C_FOM_woody,
                                                Rcpp::_["C_exudes"] = soil_output.C_exudes,
                                                Rcpp::_["C_SOM"] = soil_output.C_SOM,
                                                Rcpp::_["N_decompose_FOM"] = soil_output.N_decompose_FOM,
                                                Rcpp::_["N_decompose_SOM"] = soil_output.N_decompose_SOM,
                                                Rcpp::_["N_FOM"] = soil_output.N_FOM,
                                                Rcpp::_["N_SOM"] = soil_output.N_SOM,
                                                Rcpp::_["NC_ERM"] = soil_output.NC_ERM,
                                                Rcpp::_["NC_mantle"] = soil_output.NC_mantle,
                                                Rcpp::_["NC_needles"] = soil_output.NC_needles,
                                                Rcpp::_["NC_roots"] = soil_output.NC_roots,
                                                Rcpp::_["NC_woody"] = soil_output.NC_woody,
                                                Rcpp::_["NH4"] = soil_output.NH4,
                                                Rcpp::_["NO3"] = soil_output.NO3);
  Rcpp::DataFrame df4 = Rcpp::DataFrame::create(Rcpp::_["C_biomass"] = MYCOFON_output.C_biomass,
                                                Rcpp::_["C_fungal"] = MYCOFON_output.C_fungal,
                                                Rcpp::_["C_roots_NonStruct"] = MYCOFON_output.C_roots_NonStruct,
                                                Rcpp::_["C_fungal_NonStruct"] = MYCOFON_output.C_fungal_NonStruct,
                                                Rcpp::_["N_roots_NonStruct"] = MYCOFON_output.N_roots_NonStruct,
                                                Rcpp::_["N_fungal_NonStruct"] = MYCOFON_output.N_fungal_NonStruct,
                                                Rcpp::_["uptake_plant"] = MYCOFON_output.uptake_plant,
                                                Rcpp::_["uptake_NH4_plant"] = MYCOFON_output.uptake_NH4_plant,
                                                Rcpp::_["uptake_NO3_plant"] = MYCOFON_output.uptake_NO3_plant,
                                                Rcpp::_["uptake_Norg_plant"] = MYCOFON_output.uptake_Norg_plant,
                                                Rcpp::_["uptake_fungal"] = MYCOFON_output.uptake_fungal,
                                                Rcpp::_["uptake_NH4_fungal"] = MYCOFON_output.uptake_NH4_fungal,
                                                Rcpp::_["uptake_NO3_fungal"] = MYCOFON_output.uptake_NO3_fungal,
                                                Rcpp::_["uptake_Norg_fungal"] = MYCOFON_output.uptake_Norg_fungal,
                                                Rcpp::_["from_CASSIA"] = MYCOFON_output.from_CASSIA,
                                                Rcpp::_["to_CASSIA"] = MYCOFON_output.to_CASSIA,
                                                Rcpp::_["plant_exudates"] = MYCOFON_output.exudes_plant,
                                                Rcpp::_["fungal_exudates"] = MYCOFON_output.exudes_fungal);
  Rcpp::DataFrame df5 = Rcpp::DataFrame::create(Rcpp::_["GPP"] = photosynthesis_output.GPP,
                                                Rcpp::_["ET"] = photosynthesis_output.ET,
                                                Rcpp::_["SoilWater"] = photosynthesis_output.SoilWater,
                                                Rcpp::_["Plant_demand"] = MYCOFON_output.Plant_demand,
                                                Rcpp::_["Fungal_demand"] = MYCOFON_output.Fungal_demand,
                                                Rcpp::_["Plant_given"] = MYCOFON_output.Plant_given,
                                                Rcpp::_["Fungal_given"] = MYCOFON_output.Fungal_given,
                                                Rcpp::_["uptake_C_microbial_FOM"] = soil_output.C_Uptake_Microbe_FOM,
                                                Rcpp::_["uptake_NH4_microbial_FOM"] = soil_output.NH4_Uptake_Microbe_FOM,
                                                Rcpp::_["uptake_NO3_microbial_FOM"] = soil_output.NO3_Uptake_Microbe_FOM,
                                                Rcpp::_["uptake_Norg_microbial_FOM"] = soil_output.Norg_Uptake_Microbe_FOM,
                                                Rcpp::_["uptake_C_microbial_SOM"] = soil_output.C_Uptake_Microbe_SOM,
                                                Rcpp::_["uptake_NH4_microbial_SOM"] = soil_output.NH4_Uptake_Microbe_SOM,
                                                Rcpp::_["uptake_NO3_microbial_SOM"] = soil_output.NO3_Uptake_Microbe_SOM,
                                                Rcpp::_["uptake_Norg_microbial_SOM"] = soil_output.Norg_Uptake_Microbe_SOM);
  Rcpp::DataFrame df6 = Rcpp::DataFrame::create(Rcpp::_["respiration_root_growth"] = respiration_output.growth, // TODO: not soil!
                                                Rcpp::_["respiration_root_maintenance"] = respiration_output.maintenance, // TODO: not soil!
                                                Rcpp::_["respiration_microbes_FOM"] = respiration_output.microbes_FOM,
                                                Rcpp::_["respiration_microbes_SOM"] = respiration_output.microbes_SOM,
                                                Rcpp::_["respiration_mycorrhiza"] = respiration_output.mycorrhiza);

  return Rcpp::List::create(Rcpp::_["Growth"] = df,
                            Rcpp::_["Sugar"] = df2,
                            Rcpp::_["Soil"] = df3,
                            Rcpp::_["Fungal"] = df4,
                            Rcpp::_["Preles"] = df5,
                            Rcpp::_["Respiration"] = df6);

}


