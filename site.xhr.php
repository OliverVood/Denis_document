<?php

	const POINT_ENTRY = 'xhr';
	const POINT_TYPE = 'site';

	require __DIR__ . '/consts.inc';

	if (!POINT_ENTRY_SITE) die('Доступ запрещён');

	require DIR_ROOT . 'proj/site.xhr.inc';