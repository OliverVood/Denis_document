<?php

	namespace Proj\Site\Templates;

	use Base\Instance;
	use Base\Templates\Section;

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

			self::AddScripts('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');
			self::AddScripts('base_common', '/base/template/js/common.js');
			self::AddScripts('site_common', '/proj/templates/site/js/common.js');
			self::AddScripts('skin_select', '/proj/templates/site/js/skins/select.js');
			self::AddScripts('site_catalogs', '/proj/templates/site/js/catalogs.js');

			self::AddStylesheet('main', DIR_REL_TPL . 'site/css/main.css');
		}

	}

	Layout::init();