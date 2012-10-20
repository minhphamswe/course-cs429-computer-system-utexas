/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = { "mightyzero", /* Team name */

"Minh L. Pham", /* First member full name */
"minh.pham@utexas.edu", /* First member email address */

"", /* Second member full name (leave blank if none) */
"" /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) {
	int i, j;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate1_descr[] = "rotate1: Separate transpose - mirror";
void rotate1(int dim, pixel *src, pixel *dst) {
	int B = 16;
	int limit = dim >> 1;
	int i, j, ii, jj, r;
	pixel tmp;
	// Compute a Transpose
	// Block src[i][j] maps to block dst[j][i]
	for (i = 0; i < dim; i+=B)
		for (j = 0; j < dim ; j+=B)
			for (ii = i; ii < i+B; ii++)
				for (jj = j; jj < j+B; jj++)
					dst[RIDX(jj, ii, dim)] = src[RIDX(ii, jj, dim)];
	// Mirror lines
	for (i = 0; i < limit; i++) {
		r = dim-i-1;
		for (j = 0; j < dim; j++) {
			tmp = dst[RIDX(r, j, dim)];
			dst[RIDX(r, j, dim)] = dst[RIDX(i, j, dim)];
			dst[RIDX(i, j, dim)] = tmp;
		}
	}
}

char rotate2_descr[] = "rotate2: Merged transpose - mirror. Current";
void rotate2(int dim, pixel *src, pixel *dst) {
	int B = 16;
	int i, j, ii, jj;
	// Compute a Transpose
	// Block src[i][j] maps to block dst[j][i]
	for (i = 0; i < dim; i+=B)
		for (j = 0; j < dim ; j+=B)
			for (ii = i; ii < i+B; ii++)
				for (jj = j; jj < j+B; jj++)
					dst[RIDX(dim-1-jj, ii, dim)] = src[RIDX(ii, jj, dim)];
}

char rotate3_descr[] = "rotate3: Merged transpose - mirror. Reordered. Loop Invariant";
void rotate(int dim, pixel *src, pixel *dst) {
	int B = 16;
	int i, j, ii, jj, r;
	// Compute a Transpose
	// Block src[i][j] maps to block dst[j][i]
	for (i = 0; i < dim; i+=B)
		for (j = 0; j < dim ; j+=B)
			for (jj = j; jj < j+B; jj++) {
				r = dim-1-jj;
				for (ii = i; ii < i+B; ii++)
					dst[RIDX(r, ii, dim)] = src[RIDX(ii, jj, dim)];
		}
}

char rotate4_descr[] = "rotate4: Merged transpose - mirror. Loop unrolled";
void rotate4(int dim, pixel *src, pixel *dst) {
	int B = 16;
	int i, j, ii, jj, r;
	// Compute a Transpose
	// Block src[i][j] maps to block dst[j][i]
	for (i = 0; i < dim; i+=B)
		for (j = 0; j < dim ; j+=B)
			for (ii = i; ii < i+B; ii++)
				for (jj = j; jj < j+B; jj+=4) {
					r = dim-1-jj;
					dst[RIDX(r, ii, dim)] = src[RIDX(ii, jj, dim)];
					dst[RIDX(r-1, ii, dim)] = src[RIDX(ii, jj+1, dim)];
					dst[RIDX(r-2, ii, dim)] = src[RIDX(ii, jj+2, dim)];
					dst[RIDX(r-3, ii, dim)] = src[RIDX(ii, jj+3, dim)];
				}
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() {
	add_rotate_function(&naive_rotate, naive_rotate_descr);
	add_rotate_function(&rotate, rotate3_descr);
	/* ... Register additional test functions here */
	add_rotate_function(&rotate1, rotate1_descr);
	add_rotate_function(&rotate2, rotate2_descr);
	add_rotate_function(&rotate4, rotate4_descr);

}

/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
	int red;
	int green;
	int blue;
	int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) {
	return (a < b ? a : b);
}
static int max(int a, int b) {
	return (a > b ? a : b);
}

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) {
	sum->red = sum->green = sum->blue = 0;
	sum->num = 0;
	return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) {
	sum->red += (int) p.red;
	sum->green += (int) p.green;
	sum->blue += (int) p.blue;
	sum->num++;
	return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) {
	current_pixel->red = (unsigned short) (sum.red / sum.num);
	current_pixel->green = (unsigned short) (sum.green / sum.num);
	current_pixel->blue = (unsigned short) (sum.blue / sum.num);
	return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static void avg(int dim, int i, int j, pixel *src, pixel *dst) {
	int ii, jj;
	pixel_sum sum;

	initialize_pixel_sum(&sum);
	int start_i = max(i - 1, 0);
	int start_j = max(j - 1, 0);
	int end_i = min(i + 1, dim - 1);
	int end_j = min(j + 1, dim - 1);
	for (ii = start_i; ii <= end_i; ii++)
		for (jj = start_j; jj <= end_j; jj++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

	assign_sum_to_pixel(dst, sum);
}

//static void add_from(pixel *src, pixel *dst) {
//	dst->red += (unsigned short) (src->red / 9) ;
//	dst->green += (unsigned short) (src->green / 9);
//	dst->blue += (unsigned short) (src->blue / 9);
//}

static void add_from(pixel *src, pixel_sum *dst) {
	dst->red += src->red;
	dst->green += src->green;
	dst->blue += src->blue;
	dst->num++;
}

static void add_to(pixel_sum *dst, pixel *src) {
	dst->red += src->red;
	dst->green += src->green;
	dst->blue += src->blue;
	dst->num++;
}


/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) {
	int i, j;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			avg(dim, i, j, src, &dst[RIDX(i, j, dim)]);
}

char smooth_descr[] = "naive smoothing";
void smooth(int dim, pixel *src, pixel *dst) {
	naive_smooth(dim, src, dst);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth1_descr[] = "smooth1: Propagation method (doesn't work yet)";
void smooth1(int dim, pixel *src, pixel *dst) {
	int i, j;
	pixel_sum *tmp = malloc(dim*dim*sizeof(pixel_sum));

	int size = dim * dim;
	for (i = 0; i < size; i++) {
		tmp[i].red = src[i].red;
		tmp[i].green = src[i].green;
		tmp[i].blue = src[i].blue;
		tmp[i].num = 1;
	}

	// First row special case
	for (j = 0; j < dim-1; j++) {
		add_from(&src[j], &tmp[j+1]);
		add_from(&src[j], &tmp[dim+j]);
		add_from(&src[j], &tmp[dim+j+1]);

		add_to(&tmp[j], &src[j+1]);
		add_to(&tmp[j], &src[dim+j]);
		add_to(&tmp[j], &src[dim+j+1]);
	}
	// j = dim-1
	add_from(&src[j], &tmp[dim+j]);
	add_to(&tmp[j], &src[dim+j]);

	// General case
	for (i = 1; i < dim-1; i++) {
		for (j = 0; j < dim-1; j++) {
			add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i-1,j+1,dim)]);
			add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i,j+1,dim)]);
			add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i+1,j,dim)]);
			add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i+1,j+1,dim)]);

			add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i-1,j+1,dim)]);
			add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i,j+1,dim)]);
			add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i+1,j,dim)]);
			add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i+1,j+1,dim)]);
		}
		// j = dim-1
		add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i+1,j,dim)]);
		add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i+1,j,dim)]);
	}

	// Last row special case - i = dim-1
	for (j = 0; j < dim-1; j++) {
		add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i-1,j+1,dim)]);
		add_from(&src[RIDX(i,j,dim)], &tmp[RIDX(i,j+1,dim)]);

		add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i-1,j+1,dim)]);
		add_to(&tmp[RIDX(i,j,dim)], &src[RIDX(i,j+1,dim)]);
	}

	for (i = 0; i < size; i++) {
		assign_sum_to_pixel(&dst[i], tmp[i]);
	}

}

/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
	add_smooth_function(&smooth, smooth_descr);
	add_smooth_function(&naive_smooth, naive_smooth_descr);
	/* ... Register additional test functions here */
	add_smooth_function(&smooth1, smooth1_descr);
}

