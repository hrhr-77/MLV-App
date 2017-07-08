#ifndef _processing_struct_
#define _processing_struct_

/* Processing settings structure (a mess) */
typedef struct {

    /* (RAW) white and black levels */
    int black_level, white_level;

    /* Double is classy */

    /* Camera's matrix - will need to be set on opening clip, default set for 5D Mark II */
    double xyz_to_cam_matrix[9];
    /* What is used to turn XYZ produced form previious matrix into RGB image */
    double xyz_to_rgb_matrix[9];
    /* Main matrix: combined white balance + exposure + whatever the cmaera matrix does */
    double final_matrix[9];
    /* Precalculated all matrix values 0-65535 */
    int32_t * pre_calc_matrix[9];

    /* White balance */
    double     kelvin; /* from 2500 to 10000 */
    double     wb_tint; /* from -10 to +10 PLEAZ */

    /* Generic processing things */
    double     exposure_stops; /* Make this -4 to +4 STOPS */
    double     saturation; /* Slider from 0 to 2, to power of log(base2)of 3.5, so 1 stays in the middle, but max is 3.5 */

    /* The two part 'contrast' or S-curve */
    double     light_contrast_factor; /* 0 - 5 */
    double     light_contrast_range; /* 0 - 1, or how much of the value range will be affected */
    double     dark_contrast_factor; /* 0 - 5 */
    double     dark_contrast_range; /* 0 - 1, or how much of the value range will be affected */

    /* Gamma should be ~2.2 technically, but we get better highlight rolloff with values like 3 */
    double     gamma_power;
    /* Limited to 0.0 - 0.6 range, helps avoid horrible SONY(TM) HIGHLIGHTS (aka bad rolloff) */
    double     lighten;

    /* For whitebalance */
    double     wb_multipliers[3];
    
    /* These are pre-calculated curves / values for contrast and stuff 
     * will be calculated on setting changes, values 0-65535 */
    uint16_t * pre_calc_curves;
    uint16_t * pre_calc_levels; /* For black level and white level */
    uint16_t * pre_calc_gamma;
    /* For de super quick saturation algorythm (not working yet) */
    uint16_t * pre_calc_sat_x;
    int32_t  * pre_calc_sat_y;
    /* Temporary fix(to speed up the crappy one) */
    int32_t  * pre_calc_sat;

} processingObject_t;

/* Maybe save edits to MLV file as a block? */
typedef struct {
    uint8_t    blockType[4]; /* "EDIT" */
    uint32_t   blockSize;    /* total block size */
    double     kelvin;
    double     wb_tint;
    double     exposure_stops;
    double     saturation;
    double     light_contrast_factor;
    double     light_contrast_range;
    double     dark_contrast_factor;
    double     dark_contrast_range;
    double     gamma_power;
    double     lighten;
}  mlv_edit_hdr_t;

#endif