// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/CASSIA.h"
#include "../inst/include/CASSIA_types.h"
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// CASSIA_yearly
Rcpp::List CASSIA_yearly(int start_year, int end_year, Rcpp::DataFrame weather, std::vector<double> GPP_ref, std::vector<double> pPREL, Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_common, Rcpp::DataFrame pCASSIA_ratios, Rcpp::DataFrame pCASSIA_sperling, double needle_mass_in, double Throughfall, Rcpp::List settings);
RcppExport SEXP _CASSIA_CASSIA_yearly(SEXP start_yearSEXP, SEXP end_yearSEXP, SEXP weatherSEXP, SEXP GPP_refSEXP, SEXP pPRELSEXP, SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_commonSEXP, SEXP pCASSIA_ratiosSEXP, SEXP pCASSIA_sperlingSEXP, SEXP needle_mass_inSEXP, SEXP ThroughfallSEXP, SEXP settingsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type start_year(start_yearSEXP);
    Rcpp::traits::input_parameter< int >::type end_year(end_yearSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type weather(weatherSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type GPP_ref(GPP_refSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type pPREL(pPRELSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_common(pCASSIA_commonSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_ratios(pCASSIA_ratiosSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    Rcpp::traits::input_parameter< double >::type needle_mass_in(needle_mass_inSEXP);
    Rcpp::traits::input_parameter< double >::type Throughfall(ThroughfallSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type settings(settingsSEXP);
    rcpp_result_gen = Rcpp::wrap(CASSIA_yearly(start_year, end_year, weather, GPP_ref, pPREL, pCASSIA_parameters, pCASSIA_common, pCASSIA_ratios, pCASSIA_sperling, needle_mass_in, Throughfall, settings));
    return rcpp_result_gen;
END_RCPP
}
// replace_value_DataFrame
Rcpp::DataFrame replace_value_DataFrame(Rcpp::DataFrame df, double value, int ref);
RcppExport SEXP _CASSIA_replace_value_DataFrame(SEXP dfSEXP, SEXP valueSEXP, SEXP refSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    Rcpp::traits::input_parameter< double >::type value(valueSEXP);
    Rcpp::traits::input_parameter< int >::type ref(refSEXP);
    rcpp_result_gen = Rcpp::wrap(replace_value_DataFrame(df, value, ref));
    return rcpp_result_gen;
END_RCPP
}
// CASSIA_soil
Rcpp::List CASSIA_soil(int start_year, int end_year, Rcpp::DataFrame weather, std::vector<double> GPP_ref, std::vector<double> pPREL, Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_common, Rcpp::DataFrame pCASSIA_ratios, Rcpp::DataFrame pCASSIA_sperling, std::vector<double> parameters_R, double needle_mass_in, double Throughfall, int trenching_year, Rcpp::List settings);
RcppExport SEXP _CASSIA_CASSIA_soil(SEXP start_yearSEXP, SEXP end_yearSEXP, SEXP weatherSEXP, SEXP GPP_refSEXP, SEXP pPRELSEXP, SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_commonSEXP, SEXP pCASSIA_ratiosSEXP, SEXP pCASSIA_sperlingSEXP, SEXP parameters_RSEXP, SEXP needle_mass_inSEXP, SEXP ThroughfallSEXP, SEXP trenching_yearSEXP, SEXP settingsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type start_year(start_yearSEXP);
    Rcpp::traits::input_parameter< int >::type end_year(end_yearSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type weather(weatherSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type GPP_ref(GPP_refSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type pPREL(pPRELSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_common(pCASSIA_commonSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_ratios(pCASSIA_ratiosSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type parameters_R(parameters_RSEXP);
    Rcpp::traits::input_parameter< double >::type needle_mass_in(needle_mass_inSEXP);
    Rcpp::traits::input_parameter< double >::type Throughfall(ThroughfallSEXP);
    Rcpp::traits::input_parameter< int >::type trenching_year(trenching_yearSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type settings(settingsSEXP);
    rcpp_result_gen = Rcpp::wrap(CASSIA_soil(start_year, end_year, weather, GPP_ref, pPREL, pCASSIA_parameters, pCASSIA_common, pCASSIA_ratios, pCASSIA_sperling, parameters_R, needle_mass_in, Throughfall, trenching_year, settings));
    return rcpp_result_gen;
END_RCPP
}
// xylogenesis_wrapper
Rcpp::List xylogenesis_wrapper(int no_day, int day, Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_common, Rcpp::DataFrame pCASSIA_sperling, std::vector<double> extras_sperling, bool xylogenesis_option, bool environmental_effect_xylogenesis, double TAir, double n_rows, double max_ew_cells, double n_E_pot_old, double n_W_pot_old, double n_M_pot_old, double g, std::vector<double> en_growth_vector, double tau_W_old, double carbon_daily_rate_ew, double carbon_daily_rate_lw);
RcppExport SEXP _CASSIA_xylogenesis_wrapper(SEXP no_daySEXP, SEXP daySEXP, SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_commonSEXP, SEXP pCASSIA_sperlingSEXP, SEXP extras_sperlingSEXP, SEXP xylogenesis_optionSEXP, SEXP environmental_effect_xylogenesisSEXP, SEXP TAirSEXP, SEXP n_rowsSEXP, SEXP max_ew_cellsSEXP, SEXP n_E_pot_oldSEXP, SEXP n_W_pot_oldSEXP, SEXP n_M_pot_oldSEXP, SEXP gSEXP, SEXP en_growth_vectorSEXP, SEXP tau_W_oldSEXP, SEXP carbon_daily_rate_ewSEXP, SEXP carbon_daily_rate_lwSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type no_day(no_daySEXP);
    Rcpp::traits::input_parameter< int >::type day(daySEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_common(pCASSIA_commonSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type extras_sperling(extras_sperlingSEXP);
    Rcpp::traits::input_parameter< bool >::type xylogenesis_option(xylogenesis_optionSEXP);
    Rcpp::traits::input_parameter< bool >::type environmental_effect_xylogenesis(environmental_effect_xylogenesisSEXP);
    Rcpp::traits::input_parameter< double >::type TAir(TAirSEXP);
    Rcpp::traits::input_parameter< double >::type n_rows(n_rowsSEXP);
    Rcpp::traits::input_parameter< double >::type max_ew_cells(max_ew_cellsSEXP);
    Rcpp::traits::input_parameter< double >::type n_E_pot_old(n_E_pot_oldSEXP);
    Rcpp::traits::input_parameter< double >::type n_W_pot_old(n_W_pot_oldSEXP);
    Rcpp::traits::input_parameter< double >::type n_M_pot_old(n_M_pot_oldSEXP);
    Rcpp::traits::input_parameter< double >::type g(gSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type en_growth_vector(en_growth_vectorSEXP);
    Rcpp::traits::input_parameter< double >::type tau_W_old(tau_W_oldSEXP);
    Rcpp::traits::input_parameter< double >::type carbon_daily_rate_ew(carbon_daily_rate_ewSEXP);
    Rcpp::traits::input_parameter< double >::type carbon_daily_rate_lw(carbon_daily_rate_lwSEXP);
    rcpp_result_gen = Rcpp::wrap(xylogenesis_wrapper(no_day, day, pCASSIA_parameters, pCASSIA_common, pCASSIA_sperling, extras_sperling, xylogenesis_option, environmental_effect_xylogenesis, TAir, n_rows, max_ew_cells, n_E_pot_old, n_W_pot_old, n_M_pot_old, g, en_growth_vector, tau_W_old, carbon_daily_rate_ew, carbon_daily_rate_lw));
    return rcpp_result_gen;
END_RCPP
}
// plant_decision
Rcpp::List plant_decision(double C_roots_NonStruct, double N_roots_NonStruct, double C_fungal_NonStruct, double optimal_root_funga_biomass_ratio, double m);
RcppExport SEXP _CASSIA_plant_decision(SEXP C_roots_NonStructSEXP, SEXP N_roots_NonStructSEXP, SEXP C_fungal_NonStructSEXP, SEXP optimal_root_funga_biomass_ratioSEXP, SEXP mSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type C_roots_NonStruct(C_roots_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type N_roots_NonStruct(N_roots_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type C_fungal_NonStruct(C_fungal_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type optimal_root_funga_biomass_ratio(optimal_root_funga_biomass_ratioSEXP);
    Rcpp::traits::input_parameter< double >::type m(mSEXP);
    rcpp_result_gen = Rcpp::wrap(plant_decision(C_roots_NonStruct, N_roots_NonStruct, C_fungal_NonStruct, optimal_root_funga_biomass_ratio, m));
    return rcpp_result_gen;
END_RCPP
}
// myco_decision
Rcpp::List myco_decision(double N_fungal_NonStruct, double C_roots_NonStruct, double N_roots_NonStruct, double NC_fungal_opt);
RcppExport SEXP _CASSIA_myco_decision(SEXP N_fungal_NonStructSEXP, SEXP C_roots_NonStructSEXP, SEXP N_roots_NonStructSEXP, SEXP NC_fungal_optSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type N_fungal_NonStruct(N_fungal_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type C_roots_NonStruct(C_roots_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type N_roots_NonStruct(N_roots_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type NC_fungal_opt(NC_fungal_optSEXP);
    rcpp_result_gen = Rcpp::wrap(myco_decision(N_fungal_NonStruct, C_roots_NonStruct, N_roots_NonStruct, NC_fungal_opt));
    return rcpp_result_gen;
END_RCPP
}
// CASSIA_eeo
Rcpp::List CASSIA_eeo(int start_year, int end_year, Rcpp::DataFrame weather, std::vector<double> GPP_ref, std::vector<double> pPREL, Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_common, Rcpp::DataFrame pCASSIA_ratios, Rcpp::DataFrame pCASSIA_sperling, std::vector<double> parameters_R, double needle_mass_in, double Throughfall, int trenching_year, Rcpp::List settings);
RcppExport SEXP _CASSIA_CASSIA_eeo(SEXP start_yearSEXP, SEXP end_yearSEXP, SEXP weatherSEXP, SEXP GPP_refSEXP, SEXP pPRELSEXP, SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_commonSEXP, SEXP pCASSIA_ratiosSEXP, SEXP pCASSIA_sperlingSEXP, SEXP parameters_RSEXP, SEXP needle_mass_inSEXP, SEXP ThroughfallSEXP, SEXP trenching_yearSEXP, SEXP settingsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type start_year(start_yearSEXP);
    Rcpp::traits::input_parameter< int >::type end_year(end_yearSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type weather(weatherSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type GPP_ref(GPP_refSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type pPREL(pPRELSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_common(pCASSIA_commonSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_ratios(pCASSIA_ratiosSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type parameters_R(parameters_RSEXP);
    Rcpp::traits::input_parameter< double >::type needle_mass_in(needle_mass_inSEXP);
    Rcpp::traits::input_parameter< double >::type Throughfall(ThroughfallSEXP);
    Rcpp::traits::input_parameter< int >::type trenching_year(trenching_yearSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type settings(settingsSEXP);
    rcpp_result_gen = Rcpp::wrap(CASSIA_eeo(start_year, end_year, weather, GPP_ref, pPREL, pCASSIA_parameters, pCASSIA_common, pCASSIA_ratios, pCASSIA_sperling, parameters_R, needle_mass_in, Throughfall, trenching_year, settings));
    return rcpp_result_gen;
END_RCPP
}
// growth_wrapper
Rcpp::List growth_wrapper(int day, int year, double TAir, double TSoil_A, double TSoil_B, double Soil_Moisture, double PF, double GPP_ref, bool root_as_Ding, bool xylogenesis_option, bool environmental_effect_xylogenesis, bool sD_estim_T_count, Rcpp::DataFrame pCASSIA_common, Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_ratios, Rcpp::DataFrame pCASSIA_sperling, std::vector<double> extras_sperling, double CH, double B0, double en_pot_growth_old, double GPP_mean, double GPP_previous_sum, bool LH_estim, bool LN_estim, bool LD_estim, bool tests, std::vector<double> growth_in, double last_year_HH, int no_day);
RcppExport SEXP _CASSIA_growth_wrapper(SEXP daySEXP, SEXP yearSEXP, SEXP TAirSEXP, SEXP TSoil_ASEXP, SEXP TSoil_BSEXP, SEXP Soil_MoistureSEXP, SEXP PFSEXP, SEXP GPP_refSEXP, SEXP root_as_DingSEXP, SEXP xylogenesis_optionSEXP, SEXP environmental_effect_xylogenesisSEXP, SEXP sD_estim_T_countSEXP, SEXP pCASSIA_commonSEXP, SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_ratiosSEXP, SEXP pCASSIA_sperlingSEXP, SEXP extras_sperlingSEXP, SEXP CHSEXP, SEXP B0SEXP, SEXP en_pot_growth_oldSEXP, SEXP GPP_meanSEXP, SEXP GPP_previous_sumSEXP, SEXP LH_estimSEXP, SEXP LN_estimSEXP, SEXP LD_estimSEXP, SEXP testsSEXP, SEXP growth_inSEXP, SEXP last_year_HHSEXP, SEXP no_daySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type day(daySEXP);
    Rcpp::traits::input_parameter< int >::type year(yearSEXP);
    Rcpp::traits::input_parameter< double >::type TAir(TAirSEXP);
    Rcpp::traits::input_parameter< double >::type TSoil_A(TSoil_ASEXP);
    Rcpp::traits::input_parameter< double >::type TSoil_B(TSoil_BSEXP);
    Rcpp::traits::input_parameter< double >::type Soil_Moisture(Soil_MoistureSEXP);
    Rcpp::traits::input_parameter< double >::type PF(PFSEXP);
    Rcpp::traits::input_parameter< double >::type GPP_ref(GPP_refSEXP);
    Rcpp::traits::input_parameter< bool >::type root_as_Ding(root_as_DingSEXP);
    Rcpp::traits::input_parameter< bool >::type xylogenesis_option(xylogenesis_optionSEXP);
    Rcpp::traits::input_parameter< bool >::type environmental_effect_xylogenesis(environmental_effect_xylogenesisSEXP);
    Rcpp::traits::input_parameter< bool >::type sD_estim_T_count(sD_estim_T_countSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_common(pCASSIA_commonSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_ratios(pCASSIA_ratiosSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type extras_sperling(extras_sperlingSEXP);
    Rcpp::traits::input_parameter< double >::type CH(CHSEXP);
    Rcpp::traits::input_parameter< double >::type B0(B0SEXP);
    Rcpp::traits::input_parameter< double >::type en_pot_growth_old(en_pot_growth_oldSEXP);
    Rcpp::traits::input_parameter< double >::type GPP_mean(GPP_meanSEXP);
    Rcpp::traits::input_parameter< double >::type GPP_previous_sum(GPP_previous_sumSEXP);
    Rcpp::traits::input_parameter< bool >::type LH_estim(LH_estimSEXP);
    Rcpp::traits::input_parameter< bool >::type LN_estim(LN_estimSEXP);
    Rcpp::traits::input_parameter< bool >::type LD_estim(LD_estimSEXP);
    Rcpp::traits::input_parameter< bool >::type tests(testsSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type growth_in(growth_inSEXP);
    Rcpp::traits::input_parameter< double >::type last_year_HH(last_year_HHSEXP);
    Rcpp::traits::input_parameter< int >::type no_day(no_daySEXP);
    rcpp_result_gen = Rcpp::wrap(growth_wrapper(day, year, TAir, TSoil_A, TSoil_B, Soil_Moisture, PF, GPP_ref, root_as_Ding, xylogenesis_option, environmental_effect_xylogenesis, sD_estim_T_count, pCASSIA_common, pCASSIA_parameters, pCASSIA_ratios, pCASSIA_sperling, extras_sperling, CH, B0, en_pot_growth_old, GPP_mean, GPP_previous_sum, LH_estim, LN_estim, LD_estim, tests, growth_in, last_year_HH, no_day));
    return rcpp_result_gen;
END_RCPP
}
// myco_growth
Rcpp::List myco_growth(double C_fungal, double N_fungal, double C_fungal_biomass, double C_ecto, double a, double b, double CN_ratio);
RcppExport SEXP _CASSIA_myco_growth(SEXP C_fungalSEXP, SEXP N_fungalSEXP, SEXP C_fungal_biomassSEXP, SEXP C_ectoSEXP, SEXP aSEXP, SEXP bSEXP, SEXP CN_ratioSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type C_fungal(C_fungalSEXP);
    Rcpp::traits::input_parameter< double >::type N_fungal(N_fungalSEXP);
    Rcpp::traits::input_parameter< double >::type C_fungal_biomass(C_fungal_biomassSEXP);
    Rcpp::traits::input_parameter< double >::type C_ecto(C_ectoSEXP);
    Rcpp::traits::input_parameter< double >::type a(aSEXP);
    Rcpp::traits::input_parameter< double >::type b(bSEXP);
    Rcpp::traits::input_parameter< double >::type CN_ratio(CN_ratioSEXP);
    rcpp_result_gen = Rcpp::wrap(myco_growth(C_fungal, N_fungal, C_fungal_biomass, C_ecto, a, b, CN_ratio));
    return rcpp_result_gen;
END_RCPP
}
// mycofon_balence
Rcpp::List mycofon_balence(double C_biomass, double C_roots, double C_fungal, double C_ecto, double C_roots_NonStruct, double N_roots_NonStruct, double C_fungal_NonStruct, double N_fungal_NonStruct, double max_C_from_CASSIA, std::vector<double> parameters_R, double NH4, double NO3, double FOM_Norg, double T, double Tmb, double SWC, bool mycofon_stratergy, bool trenching);
RcppExport SEXP _CASSIA_mycofon_balence(SEXP C_biomassSEXP, SEXP C_rootsSEXP, SEXP C_fungalSEXP, SEXP C_ectoSEXP, SEXP C_roots_NonStructSEXP, SEXP N_roots_NonStructSEXP, SEXP C_fungal_NonStructSEXP, SEXP N_fungal_NonStructSEXP, SEXP max_C_from_CASSIASEXP, SEXP parameters_RSEXP, SEXP NH4SEXP, SEXP NO3SEXP, SEXP FOM_NorgSEXP, SEXP TSEXP, SEXP TmbSEXP, SEXP SWCSEXP, SEXP mycofon_stratergySEXP, SEXP trenchingSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type C_biomass(C_biomassSEXP);
    Rcpp::traits::input_parameter< double >::type C_roots(C_rootsSEXP);
    Rcpp::traits::input_parameter< double >::type C_fungal(C_fungalSEXP);
    Rcpp::traits::input_parameter< double >::type C_ecto(C_ectoSEXP);
    Rcpp::traits::input_parameter< double >::type C_roots_NonStruct(C_roots_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type N_roots_NonStruct(N_roots_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type C_fungal_NonStruct(C_fungal_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type N_fungal_NonStruct(N_fungal_NonStructSEXP);
    Rcpp::traits::input_parameter< double >::type max_C_from_CASSIA(max_C_from_CASSIASEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type parameters_R(parameters_RSEXP);
    Rcpp::traits::input_parameter< double >::type NH4(NH4SEXP);
    Rcpp::traits::input_parameter< double >::type NO3(NO3SEXP);
    Rcpp::traits::input_parameter< double >::type FOM_Norg(FOM_NorgSEXP);
    Rcpp::traits::input_parameter< double >::type T(TSEXP);
    Rcpp::traits::input_parameter< double >::type Tmb(TmbSEXP);
    Rcpp::traits::input_parameter< double >::type SWC(SWCSEXP);
    Rcpp::traits::input_parameter< bool >::type mycofon_stratergy(mycofon_stratergySEXP);
    Rcpp::traits::input_parameter< bool >::type trenching(trenchingSEXP);
    rcpp_result_gen = Rcpp::wrap(mycofon_balence(C_biomass, C_roots, C_fungal, C_ecto, C_roots_NonStruct, N_roots_NonStruct, C_fungal_NonStruct, N_fungal_NonStruct, max_C_from_CASSIA, parameters_R, NH4, NO3, FOM_Norg, T, Tmb, SWC, mycofon_stratergy, trenching));
    return rcpp_result_gen;
END_RCPP
}
// uptake_N
double uptake_N(double N, double T, double SWC, double N_limit, double k, double SWC_limit);
RcppExport SEXP _CASSIA_uptake_N(SEXP NSEXP, SEXP TSEXP, SEXP SWCSEXP, SEXP N_limitSEXP, SEXP kSEXP, SEXP SWC_limitSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type N(NSEXP);
    Rcpp::traits::input_parameter< double >::type T(TSEXP);
    Rcpp::traits::input_parameter< double >::type SWC(SWCSEXP);
    Rcpp::traits::input_parameter< double >::type N_limit(N_limitSEXP);
    Rcpp::traits::input_parameter< double >::type k(kSEXP);
    Rcpp::traits::input_parameter< double >::type SWC_limit(SWC_limitSEXP);
    rcpp_result_gen = Rcpp::wrap(uptake_N(N, T, SWC, N_limit, k, SWC_limit));
    return rcpp_result_gen;
END_RCPP
}
// uptake_C
double uptake_C(double C, double T, double SWC, double C_limit, double k, double SWC_limit);
RcppExport SEXP _CASSIA_uptake_C(SEXP CSEXP, SEXP TSEXP, SEXP SWCSEXP, SEXP C_limitSEXP, SEXP kSEXP, SEXP SWC_limitSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type C(CSEXP);
    Rcpp::traits::input_parameter< double >::type T(TSEXP);
    Rcpp::traits::input_parameter< double >::type SWC(SWCSEXP);
    Rcpp::traits::input_parameter< double >::type C_limit(C_limitSEXP);
    Rcpp::traits::input_parameter< double >::type k(kSEXP);
    Rcpp::traits::input_parameter< double >::type SWC_limit(SWC_limitSEXP);
    rcpp_result_gen = Rcpp::wrap(uptake_C(C, T, SWC, C_limit, k, SWC_limit));
    return rcpp_result_gen;
END_RCPP
}
// Plant_N_Uptake
Rcpp::List Plant_N_Uptake(double T, double SWC, double m, double NH4_in, double NO3_in, double FOM_in, std::vector<double> N_limits_R, std::vector<double> N_k_R, std::vector<double> SWC_limits_R, double NH4_on_NO3, double demand);
RcppExport SEXP _CASSIA_Plant_N_Uptake(SEXP TSEXP, SEXP SWCSEXP, SEXP mSEXP, SEXP NH4_inSEXP, SEXP NO3_inSEXP, SEXP FOM_inSEXP, SEXP N_limits_RSEXP, SEXP N_k_RSEXP, SEXP SWC_limits_RSEXP, SEXP NH4_on_NO3SEXP, SEXP demandSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type T(TSEXP);
    Rcpp::traits::input_parameter< double >::type SWC(SWCSEXP);
    Rcpp::traits::input_parameter< double >::type m(mSEXP);
    Rcpp::traits::input_parameter< double >::type NH4_in(NH4_inSEXP);
    Rcpp::traits::input_parameter< double >::type NO3_in(NO3_inSEXP);
    Rcpp::traits::input_parameter< double >::type FOM_in(FOM_inSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type N_limits_R(N_limits_RSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type N_k_R(N_k_RSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type SWC_limits_R(SWC_limits_RSEXP);
    Rcpp::traits::input_parameter< double >::type NH4_on_NO3(NH4_on_NO3SEXP);
    Rcpp::traits::input_parameter< double >::type demand(demandSEXP);
    rcpp_result_gen = Rcpp::wrap(Plant_N_Uptake(T, SWC, m, NH4_in, NO3_in, FOM_in, N_limits_R, N_k_R, SWC_limits_R, NH4_on_NO3, demand));
    return rcpp_result_gen;
END_RCPP
}
// Fungal_N_Uptake
Rcpp::List Fungal_N_Uptake(double T, double SWC, double NH4, double NO3, double FOM_Norg, std::vector<double> N_limits_R, std::vector<double> N_k_R, std::vector<double> SWC_k_R, double demand);
RcppExport SEXP _CASSIA_Fungal_N_Uptake(SEXP TSEXP, SEXP SWCSEXP, SEXP NH4SEXP, SEXP NO3SEXP, SEXP FOM_NorgSEXP, SEXP N_limits_RSEXP, SEXP N_k_RSEXP, SEXP SWC_k_RSEXP, SEXP demandSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type T(TSEXP);
    Rcpp::traits::input_parameter< double >::type SWC(SWCSEXP);
    Rcpp::traits::input_parameter< double >::type NH4(NH4SEXP);
    Rcpp::traits::input_parameter< double >::type NO3(NO3SEXP);
    Rcpp::traits::input_parameter< double >::type FOM_Norg(FOM_NorgSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type N_limits_R(N_limits_RSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type N_k_R(N_k_RSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type SWC_k_R(SWC_k_RSEXP);
    Rcpp::traits::input_parameter< double >::type demand(demandSEXP);
    rcpp_result_gen = Rcpp::wrap(Fungal_N_Uptake(T, SWC, NH4, NO3, FOM_Norg, N_limits_R, N_k_R, SWC_k_R, demand));
    return rcpp_result_gen;
END_RCPP
}
// Microbe_Uptake
Rcpp::List Microbe_Uptake(double C_microbe, double N_micorbe, double C_exudates, double C_soil_compartment, double NC_microbe_opt, double NH4_avaliable, double NO3_avaliable, double Norg_avaliable, double T, double SWC, double imobilisation, double assimilation, std::vector<double> N_limits_R, std::vector<double> N_k_R, std::vector<double> SWC_k_R, bool SOM_decomposers, double FOM_Norg, bool tests);
RcppExport SEXP _CASSIA_Microbe_Uptake(SEXP C_microbeSEXP, SEXP N_micorbeSEXP, SEXP C_exudatesSEXP, SEXP C_soil_compartmentSEXP, SEXP NC_microbe_optSEXP, SEXP NH4_avaliableSEXP, SEXP NO3_avaliableSEXP, SEXP Norg_avaliableSEXP, SEXP TSEXP, SEXP SWCSEXP, SEXP imobilisationSEXP, SEXP assimilationSEXP, SEXP N_limits_RSEXP, SEXP N_k_RSEXP, SEXP SWC_k_RSEXP, SEXP SOM_decomposersSEXP, SEXP FOM_NorgSEXP, SEXP testsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type C_microbe(C_microbeSEXP);
    Rcpp::traits::input_parameter< double >::type N_micorbe(N_micorbeSEXP);
    Rcpp::traits::input_parameter< double >::type C_exudates(C_exudatesSEXP);
    Rcpp::traits::input_parameter< double >::type C_soil_compartment(C_soil_compartmentSEXP);
    Rcpp::traits::input_parameter< double >::type NC_microbe_opt(NC_microbe_optSEXP);
    Rcpp::traits::input_parameter< double >::type NH4_avaliable(NH4_avaliableSEXP);
    Rcpp::traits::input_parameter< double >::type NO3_avaliable(NO3_avaliableSEXP);
    Rcpp::traits::input_parameter< double >::type Norg_avaliable(Norg_avaliableSEXP);
    Rcpp::traits::input_parameter< double >::type T(TSEXP);
    Rcpp::traits::input_parameter< double >::type SWC(SWCSEXP);
    Rcpp::traits::input_parameter< double >::type imobilisation(imobilisationSEXP);
    Rcpp::traits::input_parameter< double >::type assimilation(assimilationSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type N_limits_R(N_limits_RSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type N_k_R(N_k_RSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type SWC_k_R(SWC_k_RSEXP);
    Rcpp::traits::input_parameter< bool >::type SOM_decomposers(SOM_decomposersSEXP);
    Rcpp::traits::input_parameter< double >::type FOM_Norg(FOM_NorgSEXP);
    Rcpp::traits::input_parameter< bool >::type tests(testsSEXP);
    rcpp_result_gen = Rcpp::wrap(Microbe_Uptake(C_microbe, N_micorbe, C_exudates, C_soil_compartment, NC_microbe_opt, NH4_avaliable, NO3_avaliable, Norg_avaliable, T, SWC, imobilisation, assimilation, N_limits_R, N_k_R, SWC_k_R, SOM_decomposers, FOM_Norg, tests));
    return rcpp_result_gen;
END_RCPP
}
// preles_test_cpp
Rcpp::List preles_test_cpp(int start_year, int end_year, Rcpp::DataFrame weather, std::vector<double> pPREL, int etmodel);
RcppExport SEXP _CASSIA_preles_test_cpp(SEXP start_yearSEXP, SEXP end_yearSEXP, SEXP weatherSEXP, SEXP pPRELSEXP, SEXP etmodelSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type start_year(start_yearSEXP);
    Rcpp::traits::input_parameter< int >::type end_year(end_yearSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type weather(weatherSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type pPREL(pPRELSEXP);
    Rcpp::traits::input_parameter< int >::type etmodel(etmodelSEXP);
    rcpp_result_gen = Rcpp::wrap(preles_test_cpp(start_year, end_year, weather, pPREL, etmodel));
    return rcpp_result_gen;
END_RCPP
}
// repola_test_cpp
Rcpp::List repola_test_cpp(Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_sperling);
RcppExport SEXP _CASSIA_repola_test_cpp(SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_sperlingSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    rcpp_result_gen = Rcpp::wrap(repola_test_cpp(pCASSIA_parameters, pCASSIA_sperling));
    return rcpp_result_gen;
END_RCPP
}
// respiration_test_cpp
Rcpp::List respiration_test_cpp(Rcpp::DataFrame pCASSIA_parameters, Rcpp::DataFrame pCASSIA_common, Rcpp::DataFrame pCASSIA_ratios, Rcpp::DataFrame pCASSIA_sperling, std::vector<double> extras_sperling, int day, double TAir, double TSoil, bool temp_rise, bool Rm_acclimation, bool mN_varies, double B0);
RcppExport SEXP _CASSIA_respiration_test_cpp(SEXP pCASSIA_parametersSEXP, SEXP pCASSIA_commonSEXP, SEXP pCASSIA_ratiosSEXP, SEXP pCASSIA_sperlingSEXP, SEXP extras_sperlingSEXP, SEXP daySEXP, SEXP TAirSEXP, SEXP TSoilSEXP, SEXP temp_riseSEXP, SEXP Rm_acclimationSEXP, SEXP mN_variesSEXP, SEXP B0SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_parameters(pCASSIA_parametersSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_common(pCASSIA_commonSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_ratios(pCASSIA_ratiosSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type pCASSIA_sperling(pCASSIA_sperlingSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type extras_sperling(extras_sperlingSEXP);
    Rcpp::traits::input_parameter< int >::type day(daySEXP);
    Rcpp::traits::input_parameter< double >::type TAir(TAirSEXP);
    Rcpp::traits::input_parameter< double >::type TSoil(TSoilSEXP);
    Rcpp::traits::input_parameter< bool >::type temp_rise(temp_riseSEXP);
    Rcpp::traits::input_parameter< bool >::type Rm_acclimation(Rm_acclimationSEXP);
    Rcpp::traits::input_parameter< bool >::type mN_varies(mN_variesSEXP);
    Rcpp::traits::input_parameter< double >::type B0(B0SEXP);
    rcpp_result_gen = Rcpp::wrap(respiration_test_cpp(pCASSIA_parameters, pCASSIA_common, pCASSIA_ratios, pCASSIA_sperling, extras_sperling, day, TAir, TSoil, temp_rise, Rm_acclimation, mN_varies, B0));
    return rcpp_result_gen;
END_RCPP
}
// printColumnNames
void printColumnNames(Rcpp::DataFrame df);
RcppExport SEXP _CASSIA_printColumnNames(SEXP dfSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    printColumnNames(df);
    return R_NilValue;
END_RCPP
}
// symphony
Rcpp::List symphony(std::vector<double> params);
RcppExport SEXP _CASSIA_symphony(SEXP paramsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type params(paramsSEXP);
    rcpp_result_gen = Rcpp::wrap(symphony(params));
    return rcpp_result_gen;
END_RCPP
}
// symphony_plus
Rcpp::List symphony_plus(std::vector<double> params, std::vector<double> Photosynthesis);
RcppExport SEXP _CASSIA_symphony_plus(SEXP paramsSEXP, SEXP PhotosynthesisSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type Photosynthesis(PhotosynthesisSEXP);
    rcpp_result_gen = Rcpp::wrap(symphony_plus(params, Photosynthesis));
    return rcpp_result_gen;
END_RCPP
}
// symphony_plus_daily
Rcpp::List symphony_plus_daily(std::vector<double> params, double Photosynthesis, double C_plant, double C_FOM, double N);
RcppExport SEXP _CASSIA_symphony_plus_daily(SEXP paramsSEXP, SEXP PhotosynthesisSEXP, SEXP C_plantSEXP, SEXP C_FOMSEXP, SEXP NSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< double >::type Photosynthesis(PhotosynthesisSEXP);
    Rcpp::traits::input_parameter< double >::type C_plant(C_plantSEXP);
    Rcpp::traits::input_parameter< double >::type C_FOM(C_FOMSEXP);
    Rcpp::traits::input_parameter< double >::type N(NSEXP);
    rcpp_result_gen = Rcpp::wrap(symphony_plus_daily(params, Photosynthesis, C_plant, C_FOM, N));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_CASSIA_CASSIA_yearly", (DL_FUNC) &_CASSIA_CASSIA_yearly, 12},
    {"_CASSIA_replace_value_DataFrame", (DL_FUNC) &_CASSIA_replace_value_DataFrame, 3},
    {"_CASSIA_CASSIA_soil", (DL_FUNC) &_CASSIA_CASSIA_soil, 14},
    {"_CASSIA_xylogenesis_wrapper", (DL_FUNC) &_CASSIA_xylogenesis_wrapper, 19},
    {"_CASSIA_plant_decision", (DL_FUNC) &_CASSIA_plant_decision, 5},
    {"_CASSIA_myco_decision", (DL_FUNC) &_CASSIA_myco_decision, 4},
    {"_CASSIA_CASSIA_eeo", (DL_FUNC) &_CASSIA_CASSIA_eeo, 14},
    {"_CASSIA_growth_wrapper", (DL_FUNC) &_CASSIA_growth_wrapper, 29},
    {"_CASSIA_myco_growth", (DL_FUNC) &_CASSIA_myco_growth, 7},
    {"_CASSIA_mycofon_balence", (DL_FUNC) &_CASSIA_mycofon_balence, 18},
    {"_CASSIA_uptake_N", (DL_FUNC) &_CASSIA_uptake_N, 6},
    {"_CASSIA_uptake_C", (DL_FUNC) &_CASSIA_uptake_C, 6},
    {"_CASSIA_Plant_N_Uptake", (DL_FUNC) &_CASSIA_Plant_N_Uptake, 11},
    {"_CASSIA_Fungal_N_Uptake", (DL_FUNC) &_CASSIA_Fungal_N_Uptake, 9},
    {"_CASSIA_Microbe_Uptake", (DL_FUNC) &_CASSIA_Microbe_Uptake, 18},
    {"_CASSIA_preles_test_cpp", (DL_FUNC) &_CASSIA_preles_test_cpp, 5},
    {"_CASSIA_repola_test_cpp", (DL_FUNC) &_CASSIA_repola_test_cpp, 2},
    {"_CASSIA_respiration_test_cpp", (DL_FUNC) &_CASSIA_respiration_test_cpp, 12},
    {"_CASSIA_printColumnNames", (DL_FUNC) &_CASSIA_printColumnNames, 1},
    {"_CASSIA_symphony", (DL_FUNC) &_CASSIA_symphony, 1},
    {"_CASSIA_symphony_plus", (DL_FUNC) &_CASSIA_symphony_plus, 2},
    {"_CASSIA_symphony_plus_daily", (DL_FUNC) &_CASSIA_symphony_plus_daily, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_CASSIA(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
