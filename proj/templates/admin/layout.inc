<?php

	namespace Proj\Admin\Templates;

	use Base\Instance;
	use Base\Templates\Section;

	class Layout extends \Base\Templates\Layout {
		use Instance;

		public Section $header;
		public Section $menu;
		public Section $main;
		public Section $footer;

		public function __construct() {
			parent::__construct();

			$this->header = new Section();
			$this->menu = new Section();
			$this->main = new Section();
			$this->footer = new Section();

			self::AddScripts('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');
			self::AddScripts('main', '/base/template/js/common.js');
			self::AddScripts('general', '/proj/templates/admin/js/general.js');

			self::AddStylesheet('main', DIR_REL_TPL . 'admin/css/main.css');
		}

	}

	Layout::init();