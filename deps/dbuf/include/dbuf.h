#ifndef DBUF_H

#define DBUF_H
#define DBUF_INIT {NULL, 0}

struct dbuf {
	char *data;
	int length;
};

void dbufAppend(struct dbuf *dbuf, char *data, int length);
void dbufFree(struct dbuf *dbuf);

#endif
