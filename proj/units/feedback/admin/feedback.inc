<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'feedback/admin/feedback.structure.inc';
	require DIR_UNITS . 'feedback/admin/feedback.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Feedback extends Structure\Feedback {
		use Instance;

		public Editor\Feedback $editor_feedback;

		public Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_feedback = new Editor\Feedback(self::NAME, $this->table_feedback);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::object()->ToVar('Обратная связь', [
					$this->editor_feedback->select->GetLink('Список'),
				])
			);
		}

	}

	Feedback::init();