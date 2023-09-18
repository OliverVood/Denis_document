<?php

	const POINT_ENTRY = 'html';
	const POINT_TYPE = 'admin';

	require __DIR__ . '/consts.inc';

	if (!POINT_ENTRY_ADMIN) die('Доступ запрещён');

	require DIR_ROOT . 'proj/admin.html.inc';