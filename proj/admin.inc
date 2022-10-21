<?php

	require 'admin.consts.inc';

	require DIR_BASE . 'base.inc';
	require DIR_PROJ . 'admin.proj.inc';

	Base\Controller::instance()->Execute();

	Proj\Admin\Templates\Template::object()->Render();