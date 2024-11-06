CREATE TABLE films (
	film_id		INTEGER,
	in_file		VARCHAR NOT NULL,
	in_size		INTEGER NOT NULL,
	out_file	VARCHAR NOT NULL,
	out_size	INTEGER DEFAULT NULL,
	encode_time	INTEGER DEFAULT NULL,
	priority	SMALLINT NOT NULL,
	active		BOOL NOT NULL DEFAULT FALSE,
	enabled	BOOL NOT NULL DEFAULT TRUE,
	failed BOOL NOT NULL DEFAULT FALSE,
	PRIMARY KEY (film_id)
);

CREATE TABLE streams (
	film_id		INTEGER,
	stream_id	SMALLINT,
	stream_type	SMALLINT NOT NULL,
	title		VARCHAR NOT NULL,
	lang		CHAR(3) NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE stream_metadata_audio (
	film_id		INTEGER,
	stream_id	SMALLINT,
	codec		VARCHAR NOT NULL,
	sample_rate INTEGER NOT NULL,
	channels	SMALLINT NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE stream_metadata_video (
	film_id		INTEGER,
	stream_id	SMALLINT,
	frames		INTEGER NOT NULL,
	codec		VARCHAR NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE stream_metadata_video_resolution (
	film_id		INTEGER,
	stream_id	SMALLINT,
	width		INTEGER NOT NULL,
	height		INTEGER NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE stream_metadata_video_color (
	film_id		INTEGER,
	stream_id	SMALLINT,
	prim 		VARCHAR NOT NULL,
	matrix		VARCHAR NOT NULL,
	transfer	VARCHAR NOT NULL,
	pix_fmt		VARCHAR NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE stream_metadata_video_hdr10 (
	film_id		INTEGER,
	stream_id	SMALLINT,
	red_x		INTEGER NOT NULL,
	red_y		INTEGER NOT NULL,
	green_x		INTEGER NOT NULL,
	green_y		INTEGER NOT NULL,
	blue_x		INTEGER NOT NULL,
	blue_y		INTEGER NOT NULL,
	white_x		INTEGER NOT NULL,
	white_y		INTEGER NOT NULL,
	lum_min		INTEGER,
	lum_max		INTEGER,
	light_max	INTEGER,
	light_avg	INTEGER,
	has_plus	BOOL NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE stream_metadata_subtitle (
	film_id		INTEGER,
	stream_id	SMALLINT,
	encoding 	VARCHAR NOT NULL,
	PRIMARY KEY (film_id, stream_id),
	FOREIGN KEY (stream_id) REFERENCES films(film_id) ON UPDATE CASCADE ON DELETE CASCADE
);