#include "dir.h"
		struct strbuf name = STRBUF_INIT;
		struct strbuf first = STRBUF_INIT;
		struct strbuf sp = STRBUF_INIT;
			struct strbuf sp = STRBUF_INIT;
	if (patch->def_name && root) {
		char *s = xmalloc(root_len + strlen(patch->def_name) + 1);
		strcpy(s, root);
		strcpy(s + root_len, patch->def_name);
		free(patch->def_name);
		patch->def_name = s;
	}
	struct strbuf qname = STRBUF_INIT;
		if (sizeof(tgtfixbuf) > tgtlen)
	struct strbuf buf = STRBUF_INIT;
		if (!ce)
			die("make_cache_entry failed for path '%s'", name);
			remove_path(patch->old_name);
	struct strbuf nbuf = STRBUF_INIT;
static struct string_list limit_by_name;
static int has_include;
static void add_name_limit(const char *name, int exclude)
{
	struct string_list_item *it;

	it = string_list_append(name, &limit_by_name);
	it->util = exclude ? NULL : (void *) 1;
}
	int i;

	/* Paths outside are not touched regardless of "--include" */

	/* See if it matches any of exclude/include rule */
	for (i = 0; i < limit_by_name.nr; i++) {
		struct string_list_item *it = &limit_by_name.items[i];
		if (!fnmatch(it->string, pathname, 0))
			return (it->util != NULL);
	}

	/*
	 * If we had any include, a path that does not match any rule is
	 * not used.  Otherwise, we saw bunch of exclude rules (or none)
	 * and such a path is used.
	 */
	return !has_include;

	struct strbuf buf = STRBUF_INIT;
			add_name_limit(arg + 10, 1);
			continue;
		}
		if (!prefixcmp(arg, "--include=")) {
			add_name_limit(arg + 10, 0);
			has_include = 1;