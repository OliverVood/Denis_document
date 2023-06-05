<?php

	namespace Base\Editor\Skins\Edit;

	use Base\Editor\Skins\SkinEditHTMLElement;
	use Base\Templates\Buffering;

	class Select extends SkinEditHTMLElement {
		private array $data;

		public function __construct(string $title, string $name, array $data = [], string $default = '') {
			parent::__construct($title, $name, $default);

			$this->data = $data;
		}

		public function ToVar(mixed $value = null): string {
			Buffering::Start();
			$this->Render($value ?? $this->default);
			return Buffering::Read();
		}

		public function Render(string $value): void { ?>
			<select name = "<?= $this->name; ?>">
				<?php foreach ($this->data as $key => $text) {
					$selected = ($value == $key) ? ' selected' : '';
				?>
					<option value = "<?= $key; ?>"<?= $selected; ?>><?= $text; ?></option>
				<?php } ?>
			</select>
		<?php }

	}