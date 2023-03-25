<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'changes/admin/changes.structure.inc';
	require DIR_UNITS . 'changes/admin/changes.editor.inc';
	require DIR_UNITS . 'changes/admin/change.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Changes extends Structure\Changes {
		use Instance;

		public Editor\Changes $editor_changes;
		public Editor\Change $editor_change;

		public Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_changes = new Editor\Changes(self::NAME, $this->table_changes);
			$this->editor_change = new Editor\Change('change', $this->table_change);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Актуальное', [
					$this->editor_changes->select->GetLink('Списки актуального', ['page' => 1]),
					$this->editor_changes->create->GetLink('Добавить список актуального')
				])
			);
		}

	}

	Changes::init();