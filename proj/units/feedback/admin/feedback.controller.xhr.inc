<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'feedback/admin/feedback.structure.inc';
	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.xhr.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor\XHR as Editor;

	class Feedback extends Structure\Feedback {
		use Instance;

		public Editor\Feedback $editor_feedback;

		private function __construct() {
			parent::__construct();

			$this->editor_feedback = new Editor\Feedback(self::NAME, $this->table_feedback);
		}

	}

	Feedback::init();