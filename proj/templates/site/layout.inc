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
		}

	}

	Layout::init();