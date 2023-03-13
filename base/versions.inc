<?php

	namespace Base\Templates\Versions {

		use Base\VersionsControl;

		define("Base\Templates\Versions\COMMON_JS", VersionsControl::instance()->Get('base', 'COMMON_JS'));
	}