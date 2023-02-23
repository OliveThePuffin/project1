//
// This file contains all of the implementations of the replacement_policy
// constructors from the replacement_policies.h file.
//
// It also contains stubs of all of the functions that are added to each
// replacement_policy struct at construction time.
//
// ============================================================================
// NOTE: It is recommended that you read the comments in the
// replacement_policies.h file for further context on what each function is
// for.
// ============================================================================
//

#include "replacement_policies.h"

// LRU Replacement Policy
// ============================================================================
// TODO feel free to create additional structs/enums as necessary

struct lru_data {
	uint32_t num_lines;
	uint32_t current_time;
	uint32_t *access_times;
};

void lru_cache_access(struct replacement_policy *replacement_policy,
                      struct cache_system *cache_system, uint32_t set_idx, uint32_t tag)
{
	struct lru_data *data = (struct lru_data *)replacement_policy->data;
	data->current_time++;
	for (
			uint32_t i = set_idx * cache_system->associativity;
			i < (set_idx+1) * cache_system->associativity;
			i++) {
		if (cache_system->cache_lines[i].tag == tag) {
			data->access_times[i] = data->current_time;
			break;
		}
	}
}

uint32_t lru_eviction_index(struct replacement_policy *replacement_policy,
                            struct cache_system *cache_system, uint32_t set_idx)
{
	struct lru_data *data = (struct lru_data *)replacement_policy->data;

	uint32_t index;
	uint32_t min_time = -1;
	for (
			uint32_t i = set_idx * cache_system->associativity;
			i < (set_idx+1) * cache_system->associativity;
			i++) {
		if (data->access_times[i] < min_time) {
			min_time = data->access_times[i];
			index = i;
		}
	}
    return index % cache_system->associativity;
}

void lru_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
	free(((struct lru_data *)replacement_policy->data)->access_times);
	free(replacement_policy->data);

}

struct replacement_policy *lru_replacement_policy_new(uint32_t sets, uint32_t associativity)
{
    struct replacement_policy *lru_rp = calloc(1, sizeof(struct replacement_policy));
    lru_rp->cache_access = &lru_cache_access;
    lru_rp->eviction_index = &lru_eviction_index;
    lru_rp->cleanup = &lru_replacement_policy_cleanup;

	struct lru_data *data = calloc(1, sizeof(struct lru_data));
	data->num_lines = sets * associativity;
	data->access_times = calloc(data->num_lines, sizeof(uint32_t));
    lru_rp->data = data;

    return lru_rp;
}

// RAND Replacement Policy
// ============================================================================
void rand_cache_access(struct replacement_policy *replacement_policy,
                       struct cache_system *cache_system, uint32_t set_idx, uint32_t tag)
{
    // TODO update the RAND replacement policy state given a new memory access
}

uint32_t rand_eviction_index(struct replacement_policy *replacement_policy,
                             struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.

    return 0;
}

void rand_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // rand_replacement_policy_new function.
}

struct replacement_policy *rand_replacement_policy_new(uint32_t sets, uint32_t associativity)
{
    // Seed randomness
    srand(time(NULL));

    struct replacement_policy *rand_rp = malloc(sizeof(struct replacement_policy));
    rand_rp->cache_access = &rand_cache_access;
    rand_rp->eviction_index = &rand_eviction_index;
    rand_rp->cleanup = &rand_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    // rand_rp->data.

    return rand_rp;
}

// LRU_PREFER_CLEAN Replacement Policy
// ============================================================================
void lru_prefer_clean_cache_access(struct replacement_policy *replacement_policy,
                                   struct cache_system *cache_system, uint32_t set_idx,
                                   uint32_t tag)
{
    // TODO update the LRU_PREFER_CLEAN replacement policy state given a new
    // memory access
    // NOTE: you may be able to share code with the LRU policy
}

uint32_t lru_prefer_clean_eviction_index(struct replacement_policy *replacement_policy,
                                         struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.

    return 0;
}

void lru_prefer_clean_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // lru_prefer_clean_replacement_policy_new function.
}

struct replacement_policy *lru_prefer_clean_replacement_policy_new(uint32_t sets,
                                                                   uint32_t associativity)
{
    struct replacement_policy *lru_prefer_clean_rp = malloc(sizeof(struct replacement_policy));
    lru_prefer_clean_rp->cache_access = &lru_prefer_clean_cache_access;
    lru_prefer_clean_rp->eviction_index = &lru_prefer_clean_eviction_index;
    lru_prefer_clean_rp->cleanup = &lru_prefer_clean_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    // lru_prefer_clean_rp->data.

    return lru_prefer_clean_rp;
}
