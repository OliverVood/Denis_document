<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'statistics/admin/statistics.structure.inc';
	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.xhr.inc';
	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.xhr.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor\XHR as Editor;

	class Statistics extends Structure\Statistics {
		use Instance;

		public Editor\Ip $editor_ip;
		public Editor\Actions $editor_act;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_ip = new Editor\Ip(self::NAME . '_ip', $this->table_ip);
			$this->editor_act = new Editor\Actions(self::NAME . '_act', $this->table_act);
		}
	}

	Statistics::init();