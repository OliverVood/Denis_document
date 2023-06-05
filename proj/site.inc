<?php

	session_start();

	require DIR_ROOT . 'proj/site.consts.inc';

	require DIR_BASE . 'base.html.inc';

	require DIR_ROOT . 'proj/params.inc';
	require DIR_ROOT . 'proj/site.versions.inc';
	require DIR_PROJ . 'site.proj.inc';

	Base\Controller::Execute();

	Proj\Site\Templates\Template::Render();