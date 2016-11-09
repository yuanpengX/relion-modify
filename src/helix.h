/***************************************************************************
 *
 * Author: "Shaoda He"
 * MRC Laboratory of Molecular Biology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/

#ifndef HELIX_H_
#define HELIX_H_

#include "src/multidim_array.h"
#include "src/macros.h"
#include "src/complex.h"
#include "src/fftw.h"
#include "src/image.h"
#include "src/transformations.h"
#include "src/euler.h"
#include "src/assembly.h"

#define CART_TO_HELICAL_COORDS true
#define HELICAL_TO_CART_COORDS false
#define RELION_STAR_FORMAT 0
#define XIMDISP_COORDS_FORMAT 1
#define EMAN2_FORMAT 2
#define UNIMODAL_PSI_PRIOR_FLIP_RATIO (0.)
#define BIMODAL_PSI_PRIOR_FLIP_RATIO (0.5)

class HelicalSymmetryItem
{
public:
	RFLOAT twist_deg;
	RFLOAT rise_pix;
	RFLOAT dev;

	HelicalSymmetryItem()
	{
		twist_deg = rise_pix = -1.;
		dev = (1e35);
	}
	HelicalSymmetryItem(RFLOAT _twist_deg, RFLOAT _rise_pix, RFLOAT _dev = (1e35))
	{
		twist_deg = _twist_deg;
		rise_pix = _rise_pix;
		dev = _dev;
	}
};

void makeHelicalSymmetryList(
		std::vector<HelicalSymmetryItem>& list,
		RFLOAT rise_min_pix,
		RFLOAT rise_max_pix,
		RFLOAT rise_step_pix,
		bool search_rise,
		RFLOAT twist_min_deg,
		RFLOAT twist_max_deg,
		RFLOAT twist_step_deg,
		bool search_twist);

bool calcCCofHelicalSymmetry(
		const MultidimArray<RFLOAT>& v,
		RFLOAT r_min_pix,
		RFLOAT r_max_pix,
		RFLOAT z_percentage,
		RFLOAT rise_pix,
		RFLOAT twist_deg,
		RFLOAT& cc,
		int& nr_asym_voxels);

void checkRangesForLocalSearchHelicalSymmetry(
		RFLOAT rise_A,
		RFLOAT rise_min_A,
		RFLOAT rise_max_A,
		RFLOAT twist_deg,
		RFLOAT twist_min_deg,
		RFLOAT twist_max_deg);

bool localSearchHelicalSymmetry(
		const MultidimArray<RFLOAT>& v,
		RFLOAT pixel_size_A,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_inner_radius_A,
		RFLOAT cyl_outer_radius_A,
		RFLOAT z_percentage,
		RFLOAT rise_min_A,
		RFLOAT rise_max_A,
		RFLOAT rise_inistep_A,
		RFLOAT& rise_refined_A,
		RFLOAT twist_min_deg,
		RFLOAT twist_max_deg,
		RFLOAT twist_inistep_deg,
		RFLOAT& twist_refined_deg);

RFLOAT getHelicalSigma2Rot(
		RFLOAT helical_rise_pix,
		RFLOAT helical_twist_deg,
		RFLOAT helical_offset_step_pix,
		RFLOAT rot_step_deg,
		RFLOAT old_sigma2_rot);

// Assume all parameters are within range
RFLOAT get_lenZ_percentage_max(
		int box_len,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_outer_radius_A,
		RFLOAT pixel_size_A);

// Assume all parameters are within range
RFLOAT get_rise_A_max(
		int box_len,
		RFLOAT pixel_size_A,
		RFLOAT lenZ_percentage,
		RFLOAT nr_units_min);

void checkHelicalParametersFor3DHelicalReference(
		int box_len,
		RFLOAT pixel_size_A,
		RFLOAT twist_deg,
		RFLOAT rise_A,
		RFLOAT lenZ_percentage,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_inner_radius_A,
		RFLOAT cyl_outer_radius_A);

void imposeHelicalSymmetryInRealSpace(
		MultidimArray<RFLOAT>& v,
		RFLOAT pixel_size_A,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_inner_radius_A,
		RFLOAT cyl_outer_radius_A,
		RFLOAT z_percentage,
		RFLOAT rise_A,
		RFLOAT twist_deg,
		RFLOAT cosine_width_pix);

/*
void searchCnZSymmetry(
		const MultidimArray<RFLOAT>& v,
		RFLOAT r_min_pix,
		RFLOAT r_max_pix,
		int cn_start,
		int cn_end,
		std::vector<RFLOAT>& cn_list,
		std::vector<RFLOAT>& cc_list,
		std::vector<int>& nr_asym_voxels_list,
		std::ofstream* fout_ptr = NULL);
*/

/*
RFLOAT calcCCofPsiFor2DHelicalSegment(
		const MultidimArray<RFLOAT>& v,
		RFLOAT psi_deg,
		RFLOAT pixel_size_A,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_outer_radius_A);


RFLOAT localSearchPsiFor2DHelicalSegment(
		const MultidimArray<RFLOAT>& v,
		RFLOAT pixel_size_A,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_outer_radius_A,
		RFLOAT ori_psi_deg,
		RFLOAT search_half_range_deg,
		RFLOAT search_step_deg);

RFLOAT searchPsiFor2DHelicalSegment(
		const MultidimArray<RFLOAT>& v,
		RFLOAT pixel_size_A,
		RFLOAT sphere_radius_A,
		RFLOAT cyl_outer_radius_A);
*/

// Some functions only for specific testing
void calcRadialAverage(
		const MultidimArray<RFLOAT>& v,
		std::vector<RFLOAT>& radial_avg_val_list);

void cutZCentralPartOfSoftMask(
		MultidimArray<RFLOAT>& mask,
		RFLOAT z_percentage,
		RFLOAT cosine_width = 5.);

void createCylindricalReference(
		MultidimArray<RFLOAT>& v,
		int box_size,
		RFLOAT inner_diameter_pix,
		RFLOAT outer_diameter_pix,
		RFLOAT cosine_width = 5.);

void transformCartesianAndHelicalCoords(
		Matrix1D<RFLOAT>& in,
		Matrix1D<RFLOAT>& out,
		RFLOAT psi_deg,
		RFLOAT tilt_deg,
		bool direction);

void transformCartesianAndHelicalCoords(
		RFLOAT xin,
		RFLOAT yin,
		RFLOAT zin,
		RFLOAT& xout,
		RFLOAT& yout,
		RFLOAT& zout,
		RFLOAT psi_deg,
		RFLOAT tilt_deg,
		int dim,
		bool direction);

/*
void makeBlot(
		MultidimArray<RFLOAT>& v,
		RFLOAT y,
		RFLOAT x,
		RFLOAT r);
*/

// C1 Helix
// If radius_A < 0, detect the radius of original assembly and calculate r as sqrt(x^2 + y^2)
void makeSimpleHelixFromPDBParticle(
		const Assembly& ori,
		Assembly& helix,
		RFLOAT radius_A,
		RFLOAT twist_deg,
		RFLOAT rise_A,
		int nr_copy,
		bool do_center = false);

/*
void normalise2DImageSlices(
		const FileName& fn_in,
		const FileName& fn_out,
		int bg_radius,
		RFLOAT white_dust_stddev = -1.,
		RFLOAT black_dust_stddev = -1.);
*/

void applySoftSphericalMask(
		MultidimArray<RFLOAT>& v,
		RFLOAT sphere_diameter = -1.,
		RFLOAT cosine_width = 5.);

void extractHelicalSegmentsFromTubes_Multiple(
		FileName& suffix_in,
		FileName& suffix_out,
		int format_tag,
		int nr_asu,
		RFLOAT rise_A,
		RFLOAT pixel_size_A,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true,
		bool cut_into_segments = true);

void convertHelicalTubeCoordsToMetaDataTable(
		FileName& fn_in,
		MetaDataTable& MD_out,
		int& total_segments,
		int& total_tubes,
		int nr_asu,
		RFLOAT rise_A,
		RFLOAT pixel_size_A,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true,
		bool cut_into_segments = true);

void combineParticlePriorsWithKaiLocalCTF(
		FileName& fn_priors,
		FileName& fn_local_ctf,
		FileName& fn_combined);

/*
void addPriorsToParticleDataFile(
		FileName& fn_priors,
		FileName& fn_data,
		FileName& fn_out);
*/

// Files of priors: mic1_priors.star, files of local CTF: mic1_local.star
// Then suffix_priors = _priors.star, suffix_local_ctf = _local.star
void combineParticlePriorsWithKaiLocalCTF_Multiple(
		std::string& suffix_priors,
		std::string& suffix_local_ctf,
		std::string& suffix_combined);

void setNullTiltPriorsInDataStar(
		FileName& fn_in,
		FileName& fn_out);

void removeBadTiltHelicalSegmentsFromDataStar(
		FileName& fn_in,
		FileName& fn_out,
		RFLOAT max_dev_deg = 15.);

void removeBadPsiHelicalSegmentsFromDataStar(
		FileName& fn_in,
		FileName& fn_out,
		RFLOAT max_dev_deg = 15.);

void convertHelicalSegmentCoordsToStarFile_Multiple(
		FileName& suffix_coords,
		FileName& suffix_out,
		int format_tag,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT boxsize,
		bool bimodal_angular_priors = true);

void convertHelicalSegmentCoordsToMetaDataTable(
		FileName& fn_in,
		MetaDataTable& MD_out,
		int& total_segments,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true);

void convertXimdispHelicalSegmentCoordsToMetaDataTable(
		FileName& fn_in,
		MetaDataTable& MD_out,
		int& total_segments,
		int& total_tubes,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true);

void convertXimdispHelicalTubeCoordsToMetaDataTable(
		FileName& fn_in,
		MetaDataTable& MD_out,
		int& total_segments,
		int& total_tubes,
		int nr_asu,
		RFLOAT rise_A,
		RFLOAT pixel_size_A,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true,
		bool cut_into_segments = true);

void convertEmanHelicalSegmentCoordsToMetaDataTable(
		FileName& fn_in,
		MetaDataTable& MD_out,
		int& total_segments,
		int& total_tubes,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true);

void convertEmanHelicalTubeCoordsToMetaDataTable(
		FileName& fn_in,
		MetaDataTable& MD_out,
		int& total_segments,
		int& total_tubes,
		int nr_asu,
		RFLOAT rise_A,
		RFLOAT pixel_size_A,
		RFLOAT Xdim,
		RFLOAT Ydim,
		RFLOAT box_size_pix,
		bool bimodal_angular_priors = true,
		bool cut_into_segments = true);

/*
void divideHelicalSegmentsFromMultipleMicrographsIntoRandomHalves(
		FileName& fn_in,
		FileName& fn_out,
		int random_seed = -1);
*/

void makeHelicalReference2D(
		MultidimArray<RFLOAT>& out,
		int box_size,
		RFLOAT particle_diameter_A,
		RFLOAT tube_diameter_A,
		RFLOAT pixel_size_A,
		bool is_tube_white = true);

void makeHelicalReference3D(
		MultidimArray<RFLOAT>& out,
		int box_size,
		RFLOAT pixel_size_A,
		RFLOAT twist_deg,
		RFLOAT rise_A,
		RFLOAT tube_diameter_A,
		RFLOAT particle_diameter_A,
		int sym_Cn);

/*
void makeHelicalReconstructionStarFileFromSingle2DClassAverage(
		FileName& fn_in_class2D,
		FileName& fn_out_star,
		RFLOAT pixel_size_A,
		RFLOAT twist_deg,
		RFLOAT rise_A,
		RFLOAT tilt_deg,
		RFLOAT psi_deg,
		int nr_projections);
*/

void divideStarFile(
		FileName& fn_in,
		int nr);

void mergeStarFiles(FileName& fn_in);

void sortHelicalTubeID(MetaDataTable& MD);

void simulateHelicalSegments(
		FileName& fn_out,
		int nr_subunits,
		int nr_asu,
		int nr_tubes,
		bool do_bimodal_searches,
		RFLOAT rise_pix,
		RFLOAT twist_deg,
		RFLOAT sigma_psi,
		RFLOAT sigma_tilt,
		int random_seed = -1);

void outputHelicalSymmetryStatus(
		int iter,
		RFLOAT rise_initial_A,
		RFLOAT rise_min_A,
		RFLOAT rise_max_A,
		RFLOAT twist_initial_deg,
		RFLOAT twist_min_deg,
		RFLOAT twist_max_deg,
		bool do_local_search_helical_symmetry,
		std::vector<RFLOAT>& rise_A,
		std::vector<RFLOAT>& twist_deg,
		RFLOAT rise_A_half1,
		RFLOAT rise_A_half2,
		RFLOAT twist_deg_half1,
		RFLOAT twist_deg_half2,
		bool do_split_random_halves,
		std::ostream& out);

void excludeLowCTFCCMicrographs(
		FileName& fn_in,
		FileName& fn_out,
		RFLOAT cc_min,
		RFLOAT EPA_lowest_res);

void cutOutPartOfHelix(
		const MultidimArray<RFLOAT>& vin,
		MultidimArray<RFLOAT>& vout,
		long int new_boxdim,
		RFLOAT ang_deg,
		RFLOAT z_percentage);

// TESTING...
class HelicalSegmentPriorInfoEntry
{
public:
	std::string helical_tube_name;
	long int MDobjectID;
	RFLOAT psi_deg, tilt_deg;
	RFLOAT dx_pix, dy_pix, dz_pix;
	RFLOAT track_pos_pix;
	bool has_wrong_polarity;
	int subset, classID;

	RFLOAT psi_prior_deg, tilt_prior_deg;
	RFLOAT dx_prior_pix, dy_prior_pix, dz_prior_pix;
	RFLOAT psi_flip_ratio;

	void clear();

	HelicalSegmentPriorInfoEntry() { clear(); };

	~HelicalSegmentPriorInfoEntry() { clear(); };

	void checkPolarity();

	bool operator<(const HelicalSegmentPriorInfoEntry &rhs) const;
};

void flipPsiTiltForHelicalSegment(
		RFLOAT old_psi,
		RFLOAT old_tilt,
		RFLOAT& new_psi,
		RFLOAT& new_tilt);

void updatePriorsForOneHelicalTube(
		std::vector<HelicalSegmentPriorInfoEntry>& list,
		int sid,
		int eid,
		int& nr_wrong_polarity,
		RFLOAT sigma_segment_dist,
		bool is_3D,
		bool do_auto_refine,
		bool do_local_angular_searches,
		bool do_exclude_out_of_range_trans,
		RFLOAT sigma2_tilt,
		RFLOAT sigma2_psi,
		RFLOAT sigma2_offset,
		RFLOAT sigma_cutoff);

void updatePriorsForHelicalReconstruction(
		MetaDataTable& MD,
		int& total_opposite_polarity,
		RFLOAT sigma_segment_dist,
		bool is_3D,
		bool do_auto_refine,
		bool do_local_angular_searches,
		RFLOAT sigma2_rot,
		RFLOAT sigma2_tilt,
		RFLOAT sigma2_psi,
		RFLOAT sigma2_offset,
		RFLOAT sigma_cutoff = 3.);
// TESTING...

void updateAngularPriorsForHelicalReconstruction(MetaDataTable& MD);

void testDataFileTransformXY(MetaDataTable& MD);

#endif /* HELIX_H_ */
