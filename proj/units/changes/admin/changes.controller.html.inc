<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'changes/admin/changes.structure.inc';
	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.html.inc';
	require DIR_UNITS . 'changes/admin/editors/change/change.editor.html.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Editor\HTML as Editor;

	class Changes extends Structure\Changes {
		use Instance;

		public Editor\Changes $editor_changes;
		public Editor\Change $editor_change;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$out_menu, [$this, 'OutMenu']);

			$this->editor_changes = new Editor\Changes(self::NAME, $this->table_changes);
			$this->editor_change = new Editor\Change('change', $this->table_change);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Актуальное', [
					$this->editor_changes->select->GetLinkHref('Списки актуального', ['page' => 1]),
					$this->editor_changes->create->GetLinkHref('Добавить список актуального')
				])
			);
		}

	}

	Changes::init();