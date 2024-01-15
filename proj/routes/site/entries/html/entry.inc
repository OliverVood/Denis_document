<?php

	session_start();

	require DIR_PROJ . 'routes/site/consts.inc';

	require DIR_PROJ . 'routes/site/entries/html/modules/base.inc';
	require DIR_PROJ . 'routes/site/entries/html/modules/proj.inc';

	require DIR_UNITS . 'consts.inc';

	require DIR_UNITS . 'site.units.inc';

	Base\Controller::Execute();

	Proj\Site\Templates\Template::Render();