<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'composition/composition.consts.inc';

	use Base\Access;
	use Base\Action;
	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Composition extends UnitAccess implements Consts\Composition {
		public static Action $new_unit;
		public static Action $new_model;
		public static Action $new_editor;
		public static Action $create_unit;
		public static Action $create_model;
		public static Action $create_editor;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		protected function RegAccess(): void {
			Access::AddCollection($this->id, $this->name, 'Композиция (единица)');
			Access::AddRight($this->id, self::ACCESS_SETTING, 'setting', 'Назначение прав');
			Access::AddRight($this->id, self::ACCESS_CREATE, 'create', 'Создание');
		}

		public static function RegActions() {
			self::$new_unit			= new Action(self::NAME, 'new_unit', 'default', /** @lang JavaScript */ "Base.Common.Query.Send('/composition/new_unit'); return false;");
			self::$new_model		= new Action(self::NAME, 'new_model', 'default', /** @lang JavaScript */ "Base.Common.Query.Send('/composition/new_model'); return false;");
			self::$new_editor		= new Action(self::NAME, 'new_editor', 'default', /** @lang JavaScript */ "Base.Common.Query.Send('/composition/new_editor'); return false;");
			self::$create_unit		= new Action(self::NAME, 'create_unit', 'default');
			self::$create_model		= new Action(self::NAME, 'create_model', 'default');
			self::$create_editor	= new Action(self::NAME, 'create_editor', 'default');
		}

	}

	Composition::RegActions();