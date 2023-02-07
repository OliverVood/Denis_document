<?php

	session_start();

	require DIR_ROOT . 'proj/site.versions.inc';
	require DIR_ROOT . 'proj/site.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'site.proj.inc';

	Base\Controller::instance()->Execute();

	Proj\Site\Templates\Template::object()->Render();