/* vi: set sw=4 ts=4: */
/*
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

#include "libbb.h"
#include "unarchive.h"

void FAST_FUNC header_verbose_list(const file_header_t *file_header)
{
	struct tm *mtime = localtime(&(file_header->mtime));

#if ENABLE_FEATURE_TAR_UNAME_GNAME
	char uid[sizeof(int)*3 + 2];
	/*char gid[sizeof(int)*3 + 2];*/
	char *user;
	char *group;

	user = file_header->tar__uname;
	if (user == NULL) {
		sprintf(uid, "%u", (unsigned)file_header->uid);
		user = uid;
	}
	group = file_header->tar__gname;
	if (group == NULL) {
		/*sprintf(gid, "%u", (unsigned)file_header->gid);*/
		group = utoa(file_header->gid);
	}
	printf("%s %s/%s %9"OFF_FMT"u %4u-%02u-%02u %02u:%02u:%02u %s",
		bb_mode_string(file_header->mode),
		user,
		group,
		file_header->size,
		1900 + mtime->tm_year,
		1 + mtime->tm_mon,
		mtime->tm_mday,
		mtime->tm_hour,
		mtime->tm_min,
		mtime->tm_sec,
		file_header->name);
#else /* !FEATURE_TAR_UNAME_GNAME */
	printf("%s %u/%u %9"OFF_FMT"u %4u-%02u-%02u %02u:%02u:%02u %s",
		bb_mode_string(file_header->mode),
		(unsigned)file_header->uid,
		(unsigned)file_header->gid,
		file_header->size,
		1900 + mtime->tm_year,
		1 + mtime->tm_mon,
		mtime->tm_mday,
		mtime->tm_hour,
		mtime->tm_min,
		mtime->tm_sec,
		file_header->name);
#endif /* FEATURE_TAR_UNAME_GNAME */

	if (file_header->link_target) {
		printf(" -> %s", file_header->link_target);
	}
	bb_putchar('\n');
}
