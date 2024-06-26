#include "../src/interval.h"
#include "../src/utils.h"
#include "test.h"

#include <stdint.h>
#include <stdlib.h>

bool test_size_1() {
	Interval i = (Interval){.start = 5, .end = 10};
	return EXPECT_EQ(Interval_size(i), 5);
}

bool test_size_2() {
	Interval i = (Interval){.start = 0, .end = 0};
	return EXPECT_EQ(Interval_size(i), 0);
}

bool test_size_none() {
	Interval i = (Interval){.start = SIZE_MAX, .end = 0};
	return EXPECT_EQ(Interval_size(i), 0);
}

bool test_contains() {
	Interval i = (Interval){.start = 5, .end = 10};
	return EXPECT(Interval_contains(i, 7));
}

bool test_contains_start() {
	Interval i = (Interval){.start = 5, .end = 10};
	return EXPECT(Interval_contains(i, 5));
}

bool test_doesnt_contains_end() {
	Interval i = (Interval){.start = 5, .end = 10};
	return EXPECT(!Interval_contains(i, 10));
}

bool test_doesnt_contain() {
	Interval i = (Interval){.start = 5, .end = 10};
	return EXPECT(!Interval_contains(i, 0));
}

bool test_intersection_1() {
	Interval a = (Interval){.start = 5, .end = 10};
	Interval b = (Interval){.start = 7, .end = 12};
	Interval intersection = Interval_intersection(a, b);
	return EXPECT_EQ(intersection.start, 7) && EXPECT_EQ(intersection.end, 10);
}

bool test_intersection_2() {
	Interval a = (Interval){.start = 5, .end = 10};
	Interval b = (Interval){.start = 10, .end = 12};
	Interval intersection = Interval_intersection(a, b);
	return EXPECT_EQ(intersection.start, 10) && EXPECT_EQ(intersection.end, 10);
}

bool test_intersection_none() {
	Interval a = (Interval){.start = 5, .end = 10};
	Interval b = (Interval){.start = 11, .end = 12};
	Interval intersection = Interval_intersection(a, b);
	return EXPECT_EQ(Interval_size(intersection), 0);
}

bool test_intervals_set_merge_contained() {
	IntervalsSet a = IntervalsSet_alloc(2);
	a.intervals[0] = (Interval){.start = 0, .end = 10};
	a.intervals[1] = (Interval){.start = 5, .end = 7};
	IntervalsSet_merge(&a);
	return EXPECT_EQ(a.nb_intervals, 1) && EXPECT_EQ(a.intervals[0].start, 0) && EXPECT_EQ(a.intervals[0].end, 10);
}

bool test_intervals_set_merge_overlap() {
	IntervalsSet a = IntervalsSet_alloc(2);
	a.intervals[0] = (Interval){.start = 0, .end = 10};
	a.intervals[1] = (Interval){.start = 5, .end = 15};
	IntervalsSet_merge(&a);
	return EXPECT_EQ(a.nb_intervals, 1) && EXPECT_EQ(a.intervals[0].start, 0) && EXPECT_EQ(a.intervals[0].end, 15);
}

bool test_intervals_set_merge_contiguous() {
	IntervalsSet a = IntervalsSet_alloc(2);
	a.intervals[0] = (Interval){.start = 0, .end = 10};
	a.intervals[1] = (Interval){.start = 10, .end = 15};
	IntervalsSet_merge(&a);
	return EXPECT_EQ(a.nb_intervals, 1) && EXPECT_EQ(a.intervals[0].start, 0) && EXPECT_EQ(a.intervals[0].end, 15);
}

bool test_intervals_set_merge_independent() {
	IntervalsSet a = IntervalsSet_alloc(2);
	a.intervals[0] = (Interval){.start = 0, .end = 10};
	a.intervals[1] = (Interval){.start = 15, .end = 20};
	IntervalsSet_merge(&a);
	return EXPECT_EQ(a.nb_intervals, 2) && EXPECT_EQ(a.intervals[0].start, 0) && EXPECT_EQ(a.intervals[0].end, 10) &&
		   EXPECT_EQ(a.intervals[1].start, 15) && EXPECT_EQ(a.intervals[1].end, 20);
}

bool test_intervals_set_union_overlap() {
	IntervalsSet a = IntervalsSet_alloc(1);
	a.intervals[0] = (Interval){.start = 0, .end = 10};
	IntervalsSet b = IntervalsSet_alloc(2);
	b.intervals[0] = (Interval){.start = 0, .end = 4};
	b.intervals[1] = (Interval){.start = 5, .end = 10};
	IntervalsSet union_ab = IntervalsSet_union(a, b);
	for (size_t i = 0; i < union_ab.nb_intervals; i++) {
		printf("[%lu, %lu]\n", union_ab.intervals[i].start, union_ab.intervals[i].end);
	}
	return EXPECT_EQ(union_ab.nb_intervals, 1) && EXPECT_EQ(union_ab.intervals[0].start, 0) &&
		   EXPECT_EQ(union_ab.intervals[0].end, 10);
}

int main() {
	Test* tests[] = {
		&(Test){"size_1",						  test_size_1						 },
		&(Test){"size_2",						  test_size_2						 },
		&(Test){"size_none",						 test_size_none					   },
		&(Test){"contains",						test_contains						 },
		&(Test){"contains_start",				  test_contains_start				 },
		&(Test){"doesnt_contains_end",			   test_doesnt_contains_end			   },
		&(Test){"doesnt_contain",				  test_doesnt_contain				 },
		&(Test){"intersection_1",				  test_intersection_1				 },
		&(Test){"intersection_2",				  test_intersection_2				 },
		&(Test){"intersection_none",				 test_intersection_none			   },
		&(Test){"intervals_set_merge_contained",	 test_intervals_set_merge_contained  },
		&(Test){"intervals_set_merge_overlap",	   test_intervals_set_merge_overlap	   },
		&(Test){"intervals_set_merge_contiguous",  test_intervals_set_merge_contiguous },
		&(Test){"intervals_set_merge_independent", test_intervals_set_merge_independent},
		&(Test){"intervals_set_union_overlap",	   test_intervals_set_union_overlap	   },
		NULL
	};

	return test("Interval", tests);
}