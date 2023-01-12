<?php

	namespace Proj\Admin\Templates;

	use Base\Instance;
	use Base\Templates\Section;
	use Base\Templates\Versions as BaseVersions;
	use Proj\Templates\Admin\Versions as AdminVersions;

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

			self::AddScript('jq', 'https://code.jquery.com/jquery-3.6.1.min.js');
			self::AddVersionScript('base_common', '/base/template/js/common', BaseVersions\COMMON_JS);
			self::AddVersionScript('admin_common', '/proj/templates/admin/js/common', AdminVersions\COMMON_JS);
			self::AddVersionScript('admin_general', '/proj/templates/admin/js/general', AdminVersions\GENERAL_JS);

			self::AddVersionStylesheet('main', DIR_REL_TPL . 'admin/css/main', AdminVersions\MAIN_CSS);
		}

	}

	Layout::init();