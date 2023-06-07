<?php

	namespace Proj\Site\Units\XHR;

	require DIR_UNITS . 'changes/site/changes.actions.inc';

	use Base\Instance;
	use Proj\Site\Actions;

	class Changes extends Actions\Changes {
		use Instance;

		private function __construct() {
			parent::__construct();
		}

	}

	Changes::init();