/*
 * SenseRank.cc
 *
 * Implements the PageRank graph centrality algorithm for word-senses.
 *
 * Copyright (c) 2008 Linas Vepstas <linas@linas.org>
 */
#include <stdio.h>
#include <math.h>

#include "FollowLink.h"
#include "ForeachWord.h"
#include "SenseRank.h"
#include "Node.h"
#include "SimpleTruthValue.h"

using namespace opencog;

SenseRank::SenseRank(void)
{
	damping_factor = 0.85;
}

SenseRank::~SenseRank()
{
}

/**
 * For each parse of the sentence, perform the ranking algo.
 */
void SenseRank::iterate(Handle h)
{
	foreach_parse(h, &SenseRank::rank_parse, this);
}

/**
 * For each parse, find some place to start. Since (at this point),
 * noun sense ranking and verb sense ranking are disjoint, start 
 * off on every word. That is, as of right now, the graph consists
 * of multplie connected components.
 */
bool SenseRank::rank_parse(Handle h)
{
	foreach_word_instance(h, &SenseRank::start_word, this);
	return false;
}

/**
 * Pick some random word sense to start at.
 */
bool SenseRank::start_word(Handle h)
{
	// Only noun-senses and verb-senses get ranked.
	std::string pos = get_pos_of_word_instance(h);
	if (pos.compare("#noun") && pos.compare("#verb")) return false;

	foreach_word_sense_of_inst(h, &SenseRank::start_sense, this);
	return false;
}

bool SenseRank::start_sense(Handle word_sense_h,
                            Handle sense_link_h)
{
	rand_walk(sense_link_h);
	return true;
}

/**
 * Compute the page rank for the indicated (word-inst,word-sense) pair.
 * The handle argument points at a (word-inst,word-sense) pair.
 * The page rank is defined as
 *
 * P(a) = (1-d) + d* sum_b w_ba / (sum_c w_bc) P(b)
 */
void SenseRank::rank_sense(Handle h)
{
	printf("Hello ranke sense world\n");
	
	foreach_sense_edge(h, &SenseRank::outer_sum, this);
}

bool SenseRank::outer_sum(Handle h, Handle edge)
{
	printf("outer sum\n");
	return false;
}

bool SenseRank::inner_sum(Handle h)
{
	printf("outer sum\n");
	return false;
}

/**
 *
 * Walk randomly over a connected component. 
 */
void SenseRank::rand_walk(Handle h)
{
	printf("Hello world\n");
	rank_sense(h);
}

/* ============================== END OF FILE ====================== */
