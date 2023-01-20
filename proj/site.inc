<?php

	session_start();

	require 'site.versions.inc';
	require 'site.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'site.proj.inc';

	Base\Controller::instance()->Execute();

	Proj\Site\Templates\Template::object()->Render();