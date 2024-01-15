<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'feedback/admin/feedback.structure.inc';

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class Feedback extends Structure\Feedback {
		use Instance;

		public Editor\Feedback $editor_feedback;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_feedback = new Editor\Feedback(EditorConsts\ID_FEEDBACK, self::NAME, $this->table_feedback, 'Обратная связь (редактор)');
		}

		public function GetMenu(): array {
			$out = [];
			if ($this->editor_feedback->Allow($this->editor_feedback::ACCESS_SELECT)) $out[] = $this->editor_feedback->select->GetLinkHref('Список', ['page' => 1]);

			return $out;
		}

	}

	Feedback::init();