<?php

	const ROUTE						= 'admin';
	const ENTRY						= 'html';

	const DIR_ROOT					= __DIR__ . '/';

	require DIR_ROOT . 'consts/consts.inc';

	require DIR_ROOT . 'setting.inc';
	require DIR_PROJ . 'routes/admin/settings.inc';

	if (!ENTRY_ADMIN) die('Доступ запрещён');

	require DIR_PROJ . 'routes/admin/entries/html/entry.inc';