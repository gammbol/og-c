#include <stdlib.h>
#include <string.h>

#include <dbuf.h>

void dbufAppend(struct dbuf *dbuf, char *data, int length) {
	dbuf->data = realloc(dbuf->data, dbuf->length + length);

	if (!dbuf->data) return;
	memcpy(&dbuf->data[dbuf->length], data, length);
	dbuf->length += length;
}

void dbufFree(struct dbuf *dbuf) {
	free(dbuf->data);
}



