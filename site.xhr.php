<?php

	const ROUTE						= 'site';
	const ENTRY						= 'xhr';

	const DIR_ROOT					= __DIR__ . '/';

	require DIR_ROOT . 'consts/consts.inc';

	require DIR_ROOT . 'setting.inc';
	require DIR_PROJ . 'routes/site/settings.inc';

	if (!ENTRY_SITE) die('Доступ запрещён');

	require DIR_PROJ . 'routes/site/entries/xhr/entry.inc';