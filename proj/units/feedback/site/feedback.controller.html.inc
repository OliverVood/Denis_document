<?php

	namespace Proj\Site\Units\HTML;

	require DIR_UNITS . 'feedback/site/feedback.actions.inc';

	use Base\Instance;
	use Proj\Site\Actions;

	class Feedback extends Actions\Feedback {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	Feedback::init();