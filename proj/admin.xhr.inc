<?php

	session_start();

	require DIR_ROOT . 'proj/admin.consts.inc';

	require DIR_BASE . 'base.xhr.inc';

	require DIR_PROJ . 'params.inc';
	require DIR_PROJ . 'admin.proj.xhr.inc';

	Base\Controller::Execute();