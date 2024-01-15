<?php

	namespace Proj\Templates\Admin\Versions {

		use Base\VersionsControl;

		define("Proj\Templates\Admin\Versions\COMMON_JS", VersionsControl::instance()->Get('admin', 'COMMON_JS'));
		define("Proj\Templates\Admin\Versions\GENERAL_JS", VersionsControl::instance()->Get('admin', 'GENERAL_JS'));
		define("Proj\Templates\Admin\Versions\USERS_JS", VersionsControl::instance()->Get('admin', 'USERS_JS'));

		define("Proj\Templates\Admin\Versions\MAIN_CSS", VersionsControl::instance()->Get('admin', 'MAIN_CSS'));
		define("Proj\Templates\Admin\Versions\AUTHORIZATION_CSS", VersionsControl::instance()->Get('admin', 'AUTHORIZATION_CSS'));
	}