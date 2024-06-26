#ifndef STREAM_GRAPH_H
#define STREAM_GRAPH_H

#include "bit_array.h"
#include "interval.h"
#include "units.h"
#include <stddef.h>
#include <stdint.h>

#include "stream_graph/events_table.h"
#include "stream_graph/key_moments_table.h"
#include "stream_graph/links_set.h"
#include "stream_graph/nodes_set.h"

typedef struct {
	KeyMomentsTable key_moments;
	TemporalNodesSet nodes;
	LinksSet links;
	EventsTable events;
	size_t scaling;
} StreamGraph;

StreamGraph StreamGraph_from_string(const char* str);
StreamGraph StreamGraph_from_file(const char* filename);
char* StreamGraph_to_string(StreamGraph* sg);
void StreamGraph_destroy(StreamGraph sg);
size_t StreamGraph_lifespan_begin(StreamGraph* sg);
size_t StreamGraph_lifespan_end(StreamGraph* sg);
void init_events_table(StreamGraph* sg);
void events_destroy(StreamGraph* sg);
char* InternalFormat_from_External_str(const char* str);

#endif // STREAM_GRAPH_H