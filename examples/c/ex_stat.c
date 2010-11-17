/*
 * ex_stat.c Copyright (c) 2010 WiredTiger
 *
 * This is an example demostrating how to query a database's statistics.
 */

#include <stdio.h>
#include <string.h>

#include <wt/wtds.h>

const char *home = "WIREDTIGER_TEST";

int main()
{
	int ret;
	WIREDTIGER_CONNECTION *conn;
	WIREDTIGER_SESSION *session;
	WIREDTIGER_CURSOR *cursor;
	const char *key;
	uint64_t value;

	if ((ret = wiredtiger_open(home, "create", &conn)) != 0 ||
	    (ret = conn->open_session(conn, NULL, &session)) != 0)
		fprintf(stderr, "Error connecting to %s: %s\n",
		    home, wiredtiger_strerror(ret));
	/* Note: further error checking omitted for clarity. */

	/* Open a cursor on the (virtual) statistics table. */
	ret = session->open_cursor(session, "statistics:", NULL, &cursor);

	while ((ret = cursor->next(cursor)) == 0) {
		cursor->get_key(cursor, &key);
		cursor->get_value(cursor, &value);

		printf("Got statistic: %s = %d\n", key, (int)value);
	}

	ret = conn->close(conn, NULL);

	return (ret);
}


