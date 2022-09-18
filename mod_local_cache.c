/*
 * FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 * Copyright (C) 2005-2014, Anthony Minessale II <anthm@freeswitch.org>
 *
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 *
 * The Initial Developer of the Original Code is
 * Anthony Minessale II <anthm@freeswitch.org>
 * Portions created by the Initial Developer are Copyright (C)
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * mod_local_cache.c -- Aron Podrigal
 *
 */
#include <switch.h>

#define MOD_LOCAL_CACHE_LONG_DESC "Local Cache Module."
#define MOD_LOCAL_CACHE_CACHE_SET "cache_set <key> <val> <ttl>"
#define MOD_LOCAL_CACHE_CACHE_GET "cache_get <key>"
#define MOD_LOCAL_CACHE_CACHE_DEL "cache_del <key>"
#define MOD_LOCAL_CACHE_CACHE_INC "cache_incr <key> <increment-by>"
#define MOD_LOCAL_CACHE_CACHE_DEC "cache_incr <key> <decrement-by>"
#define MOD_LOCAL_CACHE_CACHE_FLUSH "cache_flush"


/* Prototypes */
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_local_cache_shutdown);
SWITCH_MODULE_RUNTIME_FUNCTION(mod_local_cache_runtime);
SWITCH_MODULE_LOAD_FUNCTION(mod_local_cache_load);

/* SWITCH_MODULE_DEFINITION(name, load, shutdown, runtime)
 * Defines a switch_loadable_module_function_table_t and a static const char[] modname
 */
SWITCH_MODULE_DEFINITION(mod_local_cache, mod_local_cache_load, mod_local_cache_shutdown, NULL);


#define CACHE_MAX_SIZE 1024 * 1024

static struct {
  switch_hash_t *cache_hash;
  int running;
  int debug;
  int max_size;
  switch_thread_rwlock_t *rwlock;
  switch_memory_pool_t *pool;
} globals;


static void clean_expired_keys()
{

}

static void cache_set(const char* key, char *val, int ttl)
{

}

static void cache_get(const char* key)
{

}

static void cache_del(const char* key)
{

}

static void cache_incr(const char* key, int by, int ttl)
{

}

static void cache_decr(const char* key, int by, int ttl)
{

}

SWITCH_STANDARD_API(mod_local_cache_set)
{
  cache_set(key, val, ttl);
}

SWITCH_STANDARD_API(mod_local_cache_get)
{
  cache_get(key);
}

SWITCH_STANDARD_API(mod_local_cache_del)
{
  cache_del(key);
}

SWITCH_STANDARD_API(mod_local_cache_incr)
{
  cache_incr(key, by, ttl);
}

SWITCH_STANDARD_API(mod_local_cache_decr)
{
  cache_decr(key, by, ttl);
}

/* Macro expands to: switch_status_t mod_local_cache_load(switch_loadable_module_interface_t **module_interface, switch_memory_pool_t *pool) */
SWITCH_MODULE_LOAD_FUNCTION(mod_local_cache_load)
{
    switch_application_interface_t *app_interface;
    switch_api_interface_t *api_interface;
    /* connect my internal structure to the blank pointer passed to me */
    *module_interface = switch_loadable_module_create_module_interface(pool, modname);
    memset(&globals, 0, sizeof(globals));
    globals.pool = pool;

    switch_thread_rwlock_create(&globals.rwlock, globals.pool);
    switch_core_hash_init(&globals.cache_hash);

    SWITCH_ADD_API(api_interface, "cache_set", "Set cache value", mod_local_cache_set, MOD_LOCAL_CACHE_CACHE_SET);
    SWITCH_ADD_API(api_interface, "cache_get", "Get cache value", mod_local_cache_get, MOD_LOCAL_CACHE_CACHE_GET);
    SWITCH_ADD_API(api_interface, "cache_del", "Del cache value", mod_local_cache_del, MOD_LOCAL_CACHE_CACHE_DEL);
    SWITCH_ADD_API(api_interface, "cache_incr", "Increment cache value", mod_local_cache_incr, MOD_LOCAL_CACHE_CACHE_INC);
    SWITCH_ADD_API(api_interface, "cache_decr", "Decrement cache value", mod_local_cache_decr, MOD_LOCAL_CACHE_CACHE_DEC);

    /* indicate that the module should continue to be loaded */
    return SWITCH_STATUS_SUCCESS;
}

/*
  Called when the system shuts down
  Macro expands to: switch_status_t mod_local_cache_shutdown() */
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_local_cache_shutdown)
{
  switch_thread_rwlock_destroy(globals.rwlock);
  switch_core_hash_destroy(&globals.cache_hash);
  return SWITCH_STATUS_SUCCESS;
}


/*
  If it exists, this is called in it's own thread when the module-load completes
  If it returns anything but SWITCH_STATUS_TERM it will be called again automatically
  Macro expands to: switch_status_t mod_local_cache_runtime()
  */
SWITCH_MODULE_RUNTIME_FUNCTION(mod_local_cache_runtime)
{
    while(globals.running)
    {
        clean_expired_keys();
        switch_yield(1000 * 1000 * 60 * 10);
    }
    return SWITCH_STATUS_TERM;
}


/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4 noet
 */
