<?php

	namespace Proj\Site\Templates;

	use Base\Instance;
	use Base\Templates\Section;
	use Base\Templates\Versions as BaseVersions;
	use Proj\Templates\Site\Versions as SiteVersions;

	class Layout extends \Base\Templates\Layout {
		use Instance;

		public Section $header;
		public Section $main;
		public Section $footer;

		public function __construct() {
			parent::__construct();

			$this->header = new Section();
			$this->main = new Section();
			$this->footer = new Section();

			self::AddScript('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');

			self::AddVersionScript('base_common', '/base/template/js/common', BaseVersions\COMMON_JS);

			self::AddVersionScript('site_common', '/proj/templates/site/js/common', SiteVersions\COMMON_JS);
			self::AddVersionScript('site_general', '/proj/templates/site/js/general', SiteVersions\GENERAL_JS);
			self::AddVersionScript('site_catalogs', '/proj/templates/site/js/catalogs', SiteVersions\CATALOGS_JS);
			self::AddVersionScript('site_feedback', '/proj/templates/site/js/feedback', SiteVersions\FEEDBACK_JS);

			self::AddVersionScript('skin_select', '/proj/templates/site/js/skins/select', SiteVersions\SKIN_SELECT_JS);

			self::AddVersionStylesheet('main', DIR_REL_TPL . 'site/css/main', SiteVersions\MAIN_CSS);
		}

	}

	Layout::init();