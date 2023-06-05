<?php

	session_start();

	require DIR_ROOT . 'proj/admin.consts.inc';

	require DIR_BASE . 'base.html.inc';

	require DIR_PROJ . 'params.inc';
	require DIR_PROJ . 'admin.versions.inc';
	require DIR_PROJ . 'admin.proj.html.inc';

	Base\Controller::Execute();

	Proj\Admin\Templates\Template::Render();