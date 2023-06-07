<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'feedback/admin/feedback.structure.inc';
	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.html.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor\HTML as Editor;
	use Closure;

	class Feedback extends Structure\Feedback {
		use Instance;

		public Editor\Feedback $editor_feedback;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$out_menu, Closure::fromCallable([$this, 'OutMenu']));

			$this->editor_feedback = new Editor\Feedback(self::NAME, $this->table_feedback);
		}

		private function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Обратная связь', [
					$this->editor_feedback->select->GetLinkHref('Список', ['page' => 1]),
				])
			);
		}

	}

	Feedback::init();