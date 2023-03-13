<?php

	namespace Proj\Templates\Site\Versions {

		use Base\VersionsControl;

		define("Proj\Templates\Site\Versions\COMMON_JS", VersionsControl::instance()->Get('site', 'COMMON_JS'));
		define("Proj\Templates\Site\Versions\GENERAL_JS", VersionsControl::instance()->Get('site', 'GENERAL_JS'));
		define("Proj\Templates\Site\Versions\CATALOGS_JS", VersionsControl::instance()->Get('site', 'CATALOGS_JS'));
		define("Proj\Templates\Site\Versions\FEEDBACK_JS", VersionsControl::instance()->Get('site', 'FEEDBACK_JS'));
		define("Proj\Templates\Site\Versions\SKIN_SELECT_JS", VersionsControl::instance()->Get('site', 'SKIN_SELECT_JS'));

		define("Proj\Templates\Site\Versions\MAIN_CSS", VersionsControl::instance()->Get('site', 'MAIN_CSS'));
	}