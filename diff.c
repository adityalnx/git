#include "userdiff.h"
static void diff_filespec_load_driver(struct diff_filespec *one);
static char *run_textconv(const char *, struct diff_filespec *, size_t *);

	switch (userdiff_config_porcelain(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	switch (userdiff_config_basic(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	struct strbuf res = STRBUF_INIT;

	diff_filespec_load_driver(one);
	if (one->driver->textconv) {
		size_t size;
		mf->ptr = run_textconv(one->driver->textconv, one, &size);
		if (!mf->ptr)
			return -1;
		mf->size = size;
	}
	else {
		mf->ptr = one->data;
		mf->size = one->size;
	}
	struct strbuf name = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
		 * made to the preimage. In --dirstat-by-file mode, count
		 * damaged files, not damaged lines. This is done by
		 * counting only a single damaged line per file.
		if (DIFF_OPT_TST(options, DIRSTAT_BY_FILE) && damage > 0)
			damage = 1;
void diff_filespec_load_driver(struct diff_filespec *one)
	if (!one->driver)
		one->driver = userdiff_find_by_path(one->path);
	if (!one->driver)
		one->driver = userdiff_find_by_name("default");
	if (one->is_binary == -1) {
		diff_filespec_load_driver(one);
		if (one->driver->binary != -1)
			one->is_binary = one->driver->binary;
		else {
			if (!one->data && DIFF_FILE_VALID(one))
				diff_populate_filespec(one, 0);
			if (one->data)
				one->is_binary = buffer_is_binary(one->data,
						one->size);
			if (one->is_binary == -1)
				one->is_binary = 0;
		}
	}
static const struct userdiff_funcname *diff_funcname_pattern(struct diff_filespec *one)
	diff_filespec_load_driver(one);
	return one->driver->funcname.pattern ? &one->driver->funcname : NULL;
	/* Never use a non-valid filename anywhere if at all possible */
	name_a = DIFF_FILE_VALID(one) ? name_a : name_b;
	name_b = DIFF_FILE_VALID(two) ? name_b : name_a;

		const struct userdiff_funcname *pe;
		pe = diff_funcname_pattern(one);
		if (!pe)
			pe = diff_funcname_pattern(two);
		if (pe)
			xdiff_set_find_func(&xecfg, pe->pattern, pe->cflags);
	spec->is_binary = -1;
	struct strbuf buf = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
		struct userdiff_driver *drv = userdiff_find_by_path(attr_path);
		if (drv && drv->external)
			pgm = drv->external;
	} else if (opt_arg(arg, 0, "dirstat-by-file",
			   &options->dirstat_percent)) {
		options->output_format |= DIFF_FORMAT_DIRSTAT;
		DIFF_OPT_SET(options, DIRSTAT_BY_FILE);
	git_SHA_CTX *ctx;
	git_SHA1_Update(data->ctx, line, new_len);
	git_SHA_CTX ctx;
	git_SHA1_Init(&ctx);
		git_SHA1_Update(&ctx, buffer, len1);
	git_SHA1_Final(sha1, &ctx);

static char *run_textconv(const char *pgm, struct diff_filespec *spec,
		size_t *outsize)
{
	struct diff_tempfile temp;
	const char *argv[3];
	const char **arg = argv;
	struct child_process child;
	struct strbuf buf = STRBUF_INIT;

	prepare_temp_file(spec->path, &temp, spec);
	*arg++ = pgm;
	*arg++ = temp.name;
	*arg = NULL;

	memset(&child, 0, sizeof(child));
	child.argv = argv;
	child.out = -1;
	if (start_command(&child) != 0 ||
	    strbuf_read(&buf, child.out, 0) < 0 ||
	    finish_command(&child) != 0) {
		if (temp.name == temp.tmp_path)
			unlink(temp.name);
		error("error running textconv command '%s'", pgm);
		return NULL;
	}
	if (temp.name == temp.tmp_path)
		unlink(temp.name);

	return strbuf_detach(&buf, outsize);
}