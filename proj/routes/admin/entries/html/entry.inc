<?php

	session_start();

	require DIR_PROJ . 'routes/admin/consts.inc';

	require DIR_PROJ . 'routes/admin/entries/html/modules/base.inc';
	require DIR_PROJ . 'routes/admin/entries/html/modules/proj.inc';

	require DIR_UNITS . 'consts.inc';
	require DIR_UNITS . 'consts.editors.inc';

	require DIR_UNITS . 'admin.units.inc';

	\Proj\Admin\Units\Users::instance()->IsPossibleHTML();

	Base\Controller::Execute();

	Proj\Admin\Templates\Template::Render();