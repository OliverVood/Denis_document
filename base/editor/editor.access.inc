<?php

	namespace Base\Editor;

	require DIR_BASE . 'editor/editor.basic.inc';

	use Base;

	abstract class Access extends Basic {
		const ACCESS_SETTING		= 1;
		const ACCESS_SELECT			= 2;
		const ACCESS_BROWSE			= 3;
		const ACCESS_CREATE			= 4;
		const ACCESS_UPDATE			= 5;
		const ACCESS_DELETE			= 6;
		const ACCESS_STATE			= 7;

		const TEXT_ERROR_ACCESS			= 'Ошибка доступа. Недостаточно прав.';

		protected function __construct(int $id, string $name, string $title) {
			parent::__construct($id, $name, $title);

			$this->RegAccess();
		}

		protected function RegAccess() {
			$this->AddCollection();
			$this->AddRight(self::ACCESS_SETTING, 'setting', 'Назначение прав');
			$this->AddRight(self::ACCESS_SELECT, 'select', 'Выборка');
			$this->AddRight(self::ACCESS_BROWSE, 'browse', 'Вывод');
			$this->AddRight(self::ACCESS_CREATE, 'create', 'Создание');
			$this->AddRight(self::ACCESS_UPDATE, 'update', 'Изменение');
			$this->AddRight(self::ACCESS_DELETE, 'delete', 'Удаление');
			$this->AddRight(self::ACCESS_STATE, 'state', 'Изменение состояния');
		}

		final protected function AddCollection(): void {
			Base\Access::AddCollection($this->id, $this->name, $this->title);
		}

		final protected function AddRight(int $right, string $name, $title = ''): void {
			Base\Access::AddRight($this->id, $right, $name, $title);
		}

		final public function Allow(int $right, int $id = 0): bool {
			return Base\Access::Allow($right, $this->id, $id);
		}

		final public function Allows(array $rights, int $id = 0): bool {
			return Base\Access::Allows($rights, $this->id, $id);
		}

	}