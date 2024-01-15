<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'changes/admin/changes.structure.inc';

	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.inc';
	require DIR_UNITS . 'changes/admin/editors/change/change.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class Changes extends Structure\Changes {
		use Instance;

		public Editor\Changes $editor_changes;
		public Editor\Change $editor_change;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_changes = new Editor\Changes(EditorConsts\ID_CHANGES_CHANGES, self::NAME, $this->table_changes, 'Список актуального (редактор)');
			$this->editor_change = new Editor\Change(EditorConsts\ID_CHANGES_CHANGE, 'change', $this->table_change, 'Актуальное (редактор)');
		}

		public function GetMenu(): array {
			$out = [];
			if ($this->editor_changes->Allow($this->editor_changes::ACCESS_SELECT)) $out[] = $this->editor_changes->select->GetLinkHref('Списки актуального', ['page' => 1]);
			if ($this->editor_changes->Allow($this->editor_changes::ACCESS_CREATE)) $out[] = $this->editor_changes->create->GetLinkHref('Добавить список актуального');

			return $out;
		}

	}

	Changes::init();