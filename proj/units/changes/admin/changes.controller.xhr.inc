<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'changes/admin/changes.structure.inc';
	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.xhr.inc';
	require DIR_UNITS . 'changes/admin/editors/change/change.editor.xhr.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor\XHR as Editor;

	class Changes extends Structure\Changes {
		use Instance;

		public Editor\Changes $editor_changes;
		public Editor\Change $editor_change;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_changes = new Editor\Changes(self::NAME, $this->table_changes);
			$this->editor_change = new Editor\Change('change', $this->table_change);
		}

	}

	Changes::init();