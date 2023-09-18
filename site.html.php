<?php

	const POINT_ENTRY = 'html';
	const POINT_TYPE = 'site';

	require __DIR__ . '/consts.inc';

	if (!POINT_ENTRY_SITE) die('Доступ запрещён');

	require DIR_ROOT . 'proj/site.html.inc';