<?php

	require DIR_ROOT . 'proj/admin.versions.inc';
	require DIR_ROOT . 'proj/admin.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'admin.proj.inc';

	Base\Controller::instance()->Execute();

	Proj\Admin\Templates\Template::object()->Render();