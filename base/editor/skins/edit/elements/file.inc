<?php

	namespace Base\Editor\Skins\Edit;

	class File extends Input {
		private string $value;
		private string $accept;

		public function __construct(string $title, string $name, string $value = 'Выберите', string $accept = '') {
			parent::__construct($title, $name, 'file');

			$this->value = $value;
			$this->accept = $accept;
		}

		public function Render(string $value): void {
			$accept = $this->accept ? ' accept = "' . $this->accept . '"' : '';
		?>
			<input type = "<?= $this->type; ?>" name = "<?= $this->name; ?>" value = "<?= $this->value; ?>"<?= $accept; ?>>
		<?php }

	}