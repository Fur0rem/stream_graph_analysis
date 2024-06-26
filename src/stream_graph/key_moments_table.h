#include "../units.h"
#include <stddef.h>
#include <stdint.h>

typedef uint8_t RelativeMoment;
#define RELATIVE_MOMENT_MAX ((RelativeMoment)~0)
#define SLICE_SIZE (((size_t)RELATIVE_MOMENT_MAX) + 1)

typedef struct {
	size_t nb_moments;
	RelativeMoment* moments;
} MomentsSlice;

typedef struct {
	size_t current_slice;
	size_t current_moment;
} KeyMomentsTableIterator;

typedef struct {
	size_t nb_slices;
	MomentsSlice* slices;
	KeyMomentsTableIterator fill_info;
} KeyMomentsTable;

size_t KeyMomentsTable_nth_key_moment(KeyMomentsTable* kmt, size_t n);
void KeyMomentsTable_push_in_order(KeyMomentsTable* kmt, size_t key_moment);
KeyMomentsTable KeyMomentsTable_alloc(size_t nb_slices);
void KeyMomentsTable_alloc_slice(KeyMomentsTable* kmt, size_t slice, size_t nb_moments);
size_t KeyMomentsTable_first_moment(KeyMomentsTable* kmt);
size_t KeyMomentsTable_last_moment(KeyMomentsTable* kmt);
void KeyMomentsTable_destroy(KeyMomentsTable kmt);
size_t KeyMomentsTable_find_time_index(KeyMomentsTable* kmt, TimeId t);