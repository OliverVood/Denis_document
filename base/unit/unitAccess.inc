<?php

	namespace Base;

	abstract class UnitAccess extends Unit {
		public function __construct(int $id, string $name, string $title, string $file) {
			parent::__construct($id, $name, $title, $file);

			$this->RegAccess();
		}

		final public function Allow(int $right, int $id = 0): bool {
			return Access::Allow($right, $this->id, $id);
		}

		final public function Allows(array $rights, int $id = 0): bool {
			return Access::Allows($rights, $this->id, $id);
		}

		protected function RegAccess(): void {  }

	}