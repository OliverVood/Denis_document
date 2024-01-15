<?php

	session_start();

	require DIR_PROJ . 'routes/site/consts.inc';

	require DIR_PROJ . 'routes/site/entries/xhr/modules/base.inc';
	require DIR_PROJ . 'routes/site/entries/xhr/modules/proj.inc';

	require DIR_UNITS . 'consts.inc';

	require DIR_UNITS . 'site.units.inc';

	Base\Controller::Execute();