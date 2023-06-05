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
		public Section $js_global;
		public Section $js_loaded;

		public function __construct() {
			parent::__construct();

			$this->header = new Section();
			$this->menu = new Section();
			$this->main = new Section();
			$this->footer = new Section();
			$this->js_global = new Section();
			$this->js_loaded = new Section();
		}

	}

	Layout::init();